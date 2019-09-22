// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <symengine/sets.h>
#include <symengine/solve.h>
#include <symengine/visitor.h>
#include "algebra/algebra.h"
#include "algebra/util.h"
#include "common/assert.h"
#include "common/proof_chain_node.h"

// Necessary helpers to get std::unordered_map work

// The SymEngine::Basic hasher caches hashes
static std::hash<SymEngine::Basic> g_basic_hasher;

template <>
struct std::hash<Algebra::Expression> {
    std::size_t operator()(const Algebra::Expression& expr) const {
        return g_basic_hasher(*expr.get_basic());
    }
};

template <>
struct std::hash<std::pair<Algebra::Expression, SymEngine::set_basic>> {
    std::size_t operator()(const std::pair<Algebra::Expression, SymEngine::set_basic>& obj) const {
        size_t seed = 0;
        SymEngine::hash_combine(seed, g_basic_hasher(obj.first));
        for (const auto& iter : obj.second) {
            SymEngine::hash_combine(seed, g_basic_hasher(*iter));
        }
        return seed;
    }
};

template <>
struct std::equal_to<std::pair<Algebra::Expression, SymEngine::set_basic>> {
    bool operator()(const std::pair<Algebra::Expression, SymEngine::set_basic>& lhs,
                    const std::pair<Algebra::Expression, SymEngine::set_basic>& rhs) const {
        if (lhs.first != rhs.first)
            return false;
        for (const auto& iter : lhs.second) {
            if (!rhs.second.count(iter))
                return false;
        }
        for (const auto& iter : rhs.second) {
            if (!lhs.second.count(iter))
                return false;
        }
        return true;
    }
};

// Implementation of Algebra::System

namespace Algebra {

using ExpressionUsedSet = std::unordered_set<Expression>;

struct System::Impl {
    struct Equation {
        Expression expr;
        std::shared_ptr<Common::ProofChainNode> proof_node;
    };

    std::vector<Equation> equations;
    std::unordered_map<std::pair<Expression, SymEngine::set_basic>,
                       std::vector<std::pair<Expression, ProofList>>>
        memory;
    // std::unordered_map<Symbol, Expression> symbol_subst_map;
    bool new_equations = false;

    /// Holder of ProofChainNodes, so they do not get destructed
    std::vector<std::shared_ptr<Common::ProofChainNode>> proof_node_holder;

    /**
     * Tries to solve all possible representations of the expression expr, with the
     * provided arguments. This is a recursive call and can be very expensive.
     */
    std::vector<std::pair<Expression, ProofList>> TrySolveAll(const Expression& expr,
                                                              ExpressionUsedSet& used,
                                                              const SymEngine::set_basic& args);

    std::vector<std::weak_ptr<Common::ProofChainNode>> GetParents(
        const ProofList& proof_list) const;
};

/**
 * Solves a single equation with regard to a single symbol, there are no limits
 * about what arguments to use to represent the symbol in question.
 *
 * Eg. 3x + 2y == 0 can solve to x == -2/3y (wrt x) and y == -3/2x (wrt y).
 */
std::vector<Expression> SolveSingle(const Expression& equation, const Symbol& symbol) {
    auto soln = SymEngine::solve(SimplifyEquation(equation), symbol);

    if (!SymEngine::is_a<SymEngine::FiniteSet>(*soln)) {
        // Something might have gone wrong
        // TODO: log this (and introduce a logging system at all)
        UNREACHABLE_MSG("Solution is not a finite set {" + EquationToString(equation) + ", " +
                        symbol->__str__() + "}");
        return {};
    } else {
        const auto& container =
            SymEngine::down_cast<const SymEngine::FiniteSet&>(*soln).get_container();

        std::vector<Expression> ans;
        for (const auto& iter : container) {
            if (IsAcceptable(iter)) {
                ans.emplace_back(iter);
            }
        }
        return ans;
    }
}

std::vector<std::pair<Expression, ProofList>> System::Impl::TrySolveAll(
    const Expression& expr_, ExpressionUsedSet& used, const SymEngine::set_basic& args) {

    Expression expr = SymEngine::expand(expr_);

    auto pair = std::make_pair(expr, args);
    if (used.empty() && memory.count(pair)) {
        return memory[pair];
    }

    auto free_symbols = SymEngine::free_symbols(expr);

    bool has_unknown_value = false;
    std::vector<std::pair<Expression, ProofList>> ans;

    for (auto& iter : free_symbols) {
        Symbol symbol = SymEngine::rcp_static_cast<const SymEngine::Symbol>(iter);
        // Try to substitute a symbol
        if (args.count(iter)) // Argument
            continue;

        has_unknown_value = true;

        for (std::size_t i = 0; i < equations.size(); ++i) {
            const auto& equation = equations[i];
            if (used.count(equation.expr) || !SymEngine::has_symbol(equation.expr, *symbol))
                continue;

            // Simplify the equation to (symbol == xxx)
            auto solns = SolveSingle(equation.expr, symbol);

            used.emplace(equation.expr);
            for (const auto& soln : solns) {
                // Solve the (xxx) to expressions with only current free symbol or arguments
                auto new_args = free_symbols;
                for (const auto& iter2 : args) {
                    new_args.emplace(iter2);
                }
                new_args.erase(iter);
                auto solns2 = TrySolveAll(soln, used, new_args);

                for (const auto& [soln2, proof_list_2] : solns2) {
                    // Substitute and continue solving a next symbol
                    auto new_expr = SymEngine::expand(expr.subs({{iter, soln2}}));
                    const auto& solns3 = TrySolveAll(new_expr, used, args);
                    for (const auto& [soln3, proof_list_3] : solns3) {
                        ans.emplace_back(soln3, proof_list_3 | proof_list_2 | i);
                    }
                }

                // Try to solve it with the symbol and then simplify it.
                new_args.emplace(iter);
                solns2 = TrySolveAll(soln, used, new_args);

                for (const auto& [soln2, proof_list_2] : solns2) {
                    auto simplified = soln2 - symbol;
                    if (SymEngine::has_symbol(simplified, *symbol)) {
                        auto real_solns2 = SolveSingle(simplified, symbol);
                        for (const auto& real_soln2 : real_solns2) {
                            auto new_expr = SymEngine::expand(expr.subs({{iter, real_soln2}}));
                            const auto& solns3 = TrySolveAll(new_expr, used, args);
                            for (const auto& [soln3, proof_list_3] : solns3) {
                                ans.emplace_back(soln3, proof_list_3 | proof_list_2 | i);
                            }
                        }
                    }
                }
            }
            used.erase(equation.expr);
        }
    }

    if (has_unknown_value) { // Isn't outright solved
        // Remove repeated entries
        std::sort(ans.begin(), ans.end(),
                  [](const std::pair<Expression, ProofList>& lhs,
                     const std::pair<Expression, ProofList>& rhs) {
                      return g_basic_hasher(*lhs.first.get_basic()) <
                             g_basic_hasher(*rhs.first.get_basic());
                  });
        std::vector<std::pair<Expression, ProofList>> unique_ans;
        for (std::size_t i = 0; i < ans.size(); ++i) {
            if (i == 0 || ans[i].first != ans[i - 1].first) {
                unique_ans.emplace_back(ans[i]);
            }
        }

        if (used.empty())
            memory[pair] = unique_ans;
        return unique_ans;
    } else { // Already done
        if (used.empty())
            memory[pair] = {{expr, {}}};
        return {{expr, {}}};
    }
}

std::vector<std::weak_ptr<Common::ProofChainNode>> System::Impl::GetParents(
    const ProofList& proof_list) const {
    std::vector<std::weak_ptr<Common::ProofChainNode>> parents;
    u64 capacity = std::min(proof_list.Size(), equations.size());
    for (std::size_t i = 0; i < capacity; ++i) {
        if (proof_list.At(i)) {
            parents.emplace_back(equations[i].proof_node);
        }
    }
    return parents;
}

System::System() : impl(std::make_unique<Impl>()) {}

System::~System() = default;

void System::AddEquation(const Expression& expr, const std::string& transform,
                         const std::vector<std::shared_ptr<Common::ProofChainNode>>& parents) {
    if (CheckEquation(expr).first)
        return;

    auto proof_node = std::make_shared<Common::ProofChainNode>();
    proof_node->transform = transform;
    proof_node->statement = EquationToString(expr);
    for (const auto& iter : parents) {
        proof_node->reasons.emplace_back(iter);
    }

    impl->equations.push_back(Impl::Equation{expr, proof_node});
    impl->memory.clear();
    impl->new_equations = true;
}

std::pair<bool, std::shared_ptr<Common::ProofChainNode>> System::CheckEquation(
    const Expression& expr) {

    ExpressionUsedSet used;
    auto soln = impl->TrySolveAll(expr, used, {});

    // TODO: Why isn't everything EXACT zero?
    bool ret =
        soln.size() > 0 &&
        std::all_of(soln.begin(), soln.end(), [](const std::pair<Expression, ProofList>& expr) {
            return SymEngine::is_a_Number(*expr.first.get_basic()) &&
                   SymEngine::rcp_static_cast<const SymEngine::Number>(expr.first.get_basic())
                       ->is_zero();
        });

    if (!ret) {
        return {ret, {}};
    }

    auto proof_node = std::make_shared<Common::ProofChainNode>();
    proof_node->transform = "algebra";
    proof_node->statement = EquationToString(expr);

    // TODO: Pick a best one instead of a random one
    proof_node->reasons = impl->GetParents(soln[0].second);

    impl->proof_node_holder.emplace_back(proof_node);
    return {ret, proof_node};
}

std::vector<Expression> System::TrySolveAll(const Symbol& sym, const std::vector<Symbol>& args) {
    SymEngine::set_basic converted_args;
    for (const auto& iter : args) {
        converted_args.emplace(iter);
    }

    ExpressionUsedSet used;
    const auto& solns = impl->TrySolveAll(SymEngine::Expression(sym), used, converted_args);

    std::vector<Expression> ans;
    for (const auto& [soln, proof_list] : solns) {
        ans.emplace_back(soln);
    }
    return ans;
}

bool System::HasNewEquations() {
    bool ret = impl->new_equations;
    impl->new_equations = false;

    return ret;
}

} // namespace Algebra

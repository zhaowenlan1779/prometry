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
    std::vector<Expression> equations;
    std::unordered_map<std::pair<Expression, SymEngine::set_basic>, std::vector<Expression>> memory;
    // std::unordered_map<Symbol, Expression> symbol_subst_map;
    bool new_equations = false;

    /**
     * Tries to solve all possible representations of the expression expr, with the
     * provided arguments. This is a recursive call and can be very expensive.
     */
    std::vector<Expression> TrySolveAll(const Expression& expr, ExpressionUsedSet& used,
                                        const SymEngine::set_basic& args);
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
        UNREACHABLE_MSG("Solution is not a finite set");
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

std::vector<Expression> System::Impl::TrySolveAll(const Expression& expr_, ExpressionUsedSet& used,
                                                  const SymEngine::set_basic& args) {

    Expression expr = SymEngine::expand(expr_);

    auto pair = std::make_pair(expr, args);
    if (used.empty() && memory.count(pair)) {
        return memory[pair];
    }

    auto free_symbols = SymEngine::free_symbols(expr);

    bool has_unknown_value = false;
    std::vector<Expression> ans;

    for (auto& iter : free_symbols) {
        Symbol symbol = SymEngine::rcp_static_cast<const SymEngine::Symbol>(iter);
        // Try to substitute a symbol
        if (args.count(iter)) // Argument
            continue;

        has_unknown_value = true;

        for (const auto& equation : equations) {
            if (used.count(equation) || !SymEngine::has_symbol(equation, *symbol))
                continue;

            // Simplify the equation to (symbol == xxx)
            auto solns = SolveSingle(equation, symbol);

            used.emplace(equation);
            for (const auto& soln : solns) {
                // Solve the (xxx) to expressions with only current free symbol or arguments
                auto new_args = free_symbols;
                for (const auto& iter2 : args) {
                    new_args.emplace(iter2);
                }
                new_args.erase(iter);
                auto solns2 = TrySolveAll(soln, used, new_args);

                for (const auto& soln2 : solns2) {
                    // Substitute and continue solving a next symbol
                    auto new_expr = SymEngine::expand(expr.subs({{iter, soln2}}));
                    const auto& solns3 = TrySolveAll(new_expr, used, args);
                    ans.insert(ans.end(), solns3.begin(), solns3.end());
                }

                // Try to solve it with the symbol and then simplify it.
                new_args.emplace(iter);
                solns2 = TrySolveAll(soln, used, new_args);

                for (const auto& soln2 : solns2) {
                    auto simplified = soln2 - symbol;
                    if (SymEngine::has_symbol(simplified, *symbol)) {
                        auto real_solns2 = SolveSingle(simplified, symbol);
                        for (const auto& real_soln2 : real_solns2) {
                            auto new_expr = SymEngine::expand(expr.subs({{iter, real_soln2}}));
                            const auto& solns3 = TrySolveAll(new_expr, used, args);
                            ans.insert(ans.end(), solns3.begin(), solns3.end());
                        }
                    }
                }
            }
            used.erase(equation);
        }
    }

    if (has_unknown_value) { // Isn't outright solved
        // Remove repeated entries
        std::sort(ans.begin(), ans.end(), [](const Expression& lhs, const Expression& rhs) {
            return std::hash<Expression>()(lhs) < std::hash<Expression>()(rhs);
        });
        ans.erase(std::unique(ans.begin(), ans.end()), ans.end());

        if (used.empty())
            memory[pair] = ans;
        return ans;
    } else { // Already done
        if (used.empty())
            memory[pair] = {expr};
        return {expr};
    }
}

System::System() : impl(std::make_unique<Impl>()) {}

System::~System() = default;

void System::AddEquation(const Expression& expr) {
    if (CheckEquation(expr))
        return;

    impl->equations.emplace_back(expr);
    impl->memory.clear();
    impl->new_equations = true;
}

bool System::CheckEquation(const Expression& expr) {
    ExpressionUsedSet used;
    auto soln = impl->TrySolveAll(expr, used, {});

    // TODO: Why isn't everything EXACT zero?
    return soln.size() > 0 &&
           std::all_of(soln.begin(), soln.end(), [](const SymEngine::Expression& expr) {
               return SymEngine::is_a_Number(*expr.get_basic()) &&
                      SymEngine::rcp_static_cast<const SymEngine::Number>(expr.get_basic())
                          ->is_zero();
           });
}

std::vector<Expression> System::TrySolveAll(const Symbol& sym, const std::vector<Symbol>& args) {
    SymEngine::set_basic converted_args;
    for (const auto& iter : args) {
        converted_args.emplace(iter);
    }

    ExpressionUsedSet used;
    return impl->TrySolveAll(SymEngine::Expression(sym), used, converted_args);
}

bool System::HasNewEquations() {
    bool ret = impl->new_equations;
    impl->new_equations = false;

    return ret;
}

} // namespace Algebra

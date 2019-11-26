// Copyright 2019 Zhupengfei and others
// Licensed under the MIT License.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

namespace Algebra {

std::vector<Expression> SolveSingle(const Expression& equation, const Symbol& symbol) {
    const auto& simplified = SimplifyEquation(equation);
    auto soln = SymEngine::solve(simplified, symbol);

    if (!SymEngine::is_a<SymEngine::FiniteSet>(*soln)) {
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

// Implementation of Algebra::System

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
    SymEngine::set_basic primary_symbols;
    SymEngine::map_basic_basic symbol_subst_map;
    std::map<SymEngine::RCP<const SymEngine::Basic>, std::shared_ptr<Common::ProofChainNode>,
             SymEngine::RCPBasicKeyLess>
        symbol_subst_proof_nodes;

    bool new_equations = false;

    /// Mainly used to remove redunant algebra steps. Map of equations added to their proof node.
    std::unordered_map<Expression, std::shared_ptr<Common::ProofChainNode>> added_equations_map;

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

    std::pair<Expression, std::vector<std::shared_ptr<Common::ProofChainNode>>> SubstituteEquation(
        const Expression& expr);
};

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

std::pair<Expression, std::vector<std::shared_ptr<Common::ProofChainNode>>>
System::Impl::SubstituteEquation(const Expression& expr) {
    auto expanded = SymEngine::expand(expr);
    std::vector<std::shared_ptr<Common::ProofChainNode>> proof_nodes;

    for (const auto& subst : symbol_subst_map) {
        // This free_symbols is recalculated on every iteration to make sure
        // no unnecessary substitutions are made.
        if (SymEngine::free_symbols(*expanded.get_basic()).count(subst.first)) {
            expanded = SymEngine::expand(expanded.subs({subst}));
            proof_nodes.emplace_back(symbol_subst_proof_nodes.at(subst.first));
        }
    }

    return {SymEngine::expand(expanded), proof_nodes};
}

System::System() : impl(std::make_unique<Impl>()) {}

System::~System() = default;

void System::AddEquation(const Expression& expr, const std::string& transform,
                         const std::vector<std::shared_ptr<Common::ProofChainNode>>& parents) {

    if (CheckEquation(expr).first)
        return;

    const auto& [substituted, subst_reasons] = impl->SubstituteEquation(expr);

    // Original equation proof node
    auto original_proof_node = std::make_shared<Common::ProofChainNode>();
    original_proof_node->transform = transform;
    original_proof_node->statement = EquationToString(expr);
    for (const auto& iter : parents) {
        original_proof_node->reasons.emplace_back(iter);
    }
    impl->proof_node_holder.emplace_back(original_proof_node);
    impl->added_equations_map.insert_or_assign(SymEngine::expand(expr), original_proof_node);

    // Substituted equation proof node
    auto subst_proof_node = std::make_shared<Common::ProofChainNode>();
    subst_proof_node->transform = "algebra";
    subst_proof_node->statement = EquationToString(substituted);
    subst_proof_node->reasons.emplace_back(original_proof_node);
    subst_proof_node->reasons.insert(subst_proof_node->reasons.end(), subst_reasons.begin(),
                                     subst_reasons.end());
    impl->proof_node_holder.emplace_back(subst_proof_node);

    SymEngine::vec_basic new_symbols;
    for (const auto& symbol : SymEngine::free_symbols(*substituted.get_basic())) {
        if (!impl->primary_symbols.count(symbol)) {
            new_symbols.emplace_back(symbol);
        }
    }

    if (new_symbols.size() >= 1) {
        // This equation surely can't have existed.
        impl->new_equations = true;
        // Substitute one primary symbol.
        for (const auto& primary_symbol : new_symbols) {
            const auto& solns = SolveSingle(
                substituted, SymEngine::rcp_static_cast<const SymEngine::Symbol>(primary_symbol));
            if (solns.size() != 1) {
                continue;
            }

            // Fix size of substitution getting too big.
            // We are only exercising the substitution on condition that the den has 0/1 symbols.
            SymEngine::RCP<const SymEngine::Basic> num, den;
            SymEngine::as_numer_denom(solns[0].get_basic(), outArg(num), outArg(den));
            if (SymEngine::free_symbols(*den).size() >= 2 ||
                SymEngine::is_a<SymEngine::Add>(*den)) {
                continue;
            }

            // Add to substitute map
            impl->symbol_subst_map.emplace(primary_symbol, solns[0].get_basic());
            impl->symbol_subst_proof_nodes.emplace(primary_symbol, subst_proof_node);

            // Add symbols as primary
            for (const auto& symbol : new_symbols) {
                if (!symbol->__eq__(*primary_symbol)) {
                    impl->primary_symbols.emplace(symbol);
                }
            }

            impl->memory.clear();
            impl->new_equations = true;
            return;
        }
        // This equation cannot be used to substitute
        for (const auto& symbol : new_symbols) {
            impl->primary_symbols.emplace(symbol);
        }
    } else {
        const auto& symbols = SymEngine::free_symbols(*substituted.get_basic());
        if (symbols.empty()) { // Ignore this equation
            return;
        }
        // Attempt to use this equation to substitute one previous primary symbol
        for (const auto& primary_symbol : symbols) {
            const auto& solns = SolveSingle(
                substituted, SymEngine::rcp_static_cast<const SymEngine::Symbol>(primary_symbol));
            if (solns.size() != 1) {
                continue;
            }

            // Fix size of substitution getting too big.
            // We are only exercising the substitution on condition that the den has 0/1 symbols.
            SymEngine::RCP<const SymEngine::Basic> num, den;
            SymEngine::as_numer_denom(solns[0].get_basic(), outArg(num), outArg(den));
            if (SymEngine::free_symbols(*den).size() >= 2 ||
                SymEngine::is_a<SymEngine::Add>(*den)) {
                continue;
            }

            impl->primary_symbols.erase(primary_symbol);
            // Update previous substitution maps
            for (const auto& [symbol, substitution] : impl->symbol_subst_map) {
                if (!SymEngine::has_symbol(*substitution, *primary_symbol)) {
                    continue;
                }
                const auto& new_substitution =
                    SymEngine::expand(substitution->subs({{primary_symbol, solns[0]}}));
                auto new_proof_node = std::make_shared<Common::ProofChainNode>();
                new_proof_node->transform = "algebra";
                new_proof_node->statement =
                    EquationToString(SymEngine::sub(new_substitution, symbol));
                new_proof_node->reasons.emplace_back(impl->symbol_subst_proof_nodes.at(symbol));
                new_proof_node->reasons.emplace_back(subst_proof_node);
                impl->proof_node_holder.emplace_back(new_proof_node);

                impl->symbol_subst_map[symbol] = new_substitution;
                impl->symbol_subst_proof_nodes[symbol] = new_proof_node;
            }
            for (auto& equation : impl->equations) {
                if (!SymEngine::has_symbol(*equation.expr.get_basic(), *primary_symbol)) {
                    continue;
                }
                const auto& new_equation =
                    SymEngine::expand(equation.expr.subs({{primary_symbol, solns[0]}}));
                auto new_proof_node = std::make_shared<Common::ProofChainNode>();
                new_proof_node->transform = "algebra";
                new_proof_node->statement = EquationToString(new_equation);
                new_proof_node->reasons.emplace_back(equation.proof_node);
                new_proof_node->reasons.emplace_back(subst_proof_node);
                impl->proof_node_holder.emplace_back(new_proof_node);

                equation.expr = new_equation;
                equation.proof_node = new_proof_node;
            }
            // Add to substitute map
            impl->symbol_subst_map.emplace(primary_symbol, solns[0].get_basic());
            impl->symbol_subst_proof_nodes.emplace(primary_symbol, subst_proof_node);

            impl->memory.clear();
            impl->new_equations = true;
            return;
        }

        // This equation can't be used to substitute
    }

    impl->equations.push_back(Impl::Equation{substituted, subst_proof_node});
    impl->memory.clear();
    impl->new_equations = true;
}

std::pair<bool, std::shared_ptr<Common::ProofChainNode>> System::CheckEquation(
    const Expression& expr) {

    const auto& expanded = SymEngine::expand(expr);
    if (impl->added_equations_map.count(expanded)) {
        return {true, impl->added_equations_map.at(expanded)};
    } else if (impl->added_equations_map.count(-expanded)) {
        return {true, impl->added_equations_map.at(-expanded)};
    }

    const auto& [substituted, subst_reasons] = impl->SubstituteEquation(expr);

    ExpressionUsedSet used;
    auto soln = impl->TrySolveAll(substituted, used, {});

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

    // Substituted equation proof node
    auto subst_proof_node = std::make_shared<Common::ProofChainNode>();
    subst_proof_node->transform = "algebra";
    subst_proof_node->statement = EquationToString(substituted);

    // TODO: Pick a best one instead of a random one
    subst_proof_node->reasons = impl->GetParents(soln[0].second);

    impl->proof_node_holder.emplace_back(subst_proof_node);

    // Original equation proof node
    auto original_proof_node = std::make_shared<Common::ProofChainNode>();
    original_proof_node->transform = "algebra";
    original_proof_node->statement = EquationToString(expr);
    if (substituted != 0) {
        original_proof_node->reasons.emplace_back(subst_proof_node);
    }
    if (substituted == 0 && subst_reasons.size() == 1) {
        original_proof_node->hidden = true;
    }
    original_proof_node->reasons.insert(original_proof_node->reasons.end(), subst_reasons.begin(),
                                        subst_reasons.end());
    impl->proof_node_holder.emplace_back(original_proof_node);

    return {ret, original_proof_node};
}

bool System::HasNewEquations() {
    bool ret = impl->new_equations;
    impl->new_equations = false;

    return ret;
}

} // namespace Algebra

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <map>
#include <set>
#include <symengine/sets.h>
#include <symengine/solve.h>
#include <symengine/visitor.h>
#include "algebra/algebra.h"
#include "common/assert.h"

namespace Algebra {

struct ExpressionCompare {
    bool operator()(const Expression& lhs, const Expression& rhs) const {
        return lhs.get_basic()->compare(*rhs.get_basic());
    }
};

using ExpressionUsedMap = std::map<Expression, bool, ExpressionCompare>;

struct System::Impl {
    std::vector<Expression> equations;

    /**
     * Solves a single equation with regard to a single symbol, there are no limits
     * about what arguments to use to represent the symbol in question.
     *
     * Eg. 3x + 2y == 0 can solve to x == -2/3y (wrt x) and y == -3/2x (wrt y).
     */
    std::vector<Expression> SolveSingle(const Expression& equation, const Symbol& symbol);

    /**
     * Tries to solve all possible representations of the expression expr, with the
     * provided arguments. This is a recursive call and can be very expensive.
     */
    std::vector<Expression> TrySolveAll(const Expression& expr, ExpressionUsedMap& used,
                                        const SymEngine::set_basic& args);
};

std::vector<Expression> System::Impl::SolveSingle(const Expression& equation,
                                                  const Symbol& symbol) {
    auto symbol_ptr = symbol.rcp_from_this();
    // In geometry problems, we will assume that all variables are positive (> 0).
    // TODO: If necessary, this limit can be loosened.
    auto soln = SymEngine::solve(
        equation, SymEngine::rcp_static_cast<const Symbol>(symbol_ptr),
        SymEngine::conditionset(symbol_ptr, SymEngine::Gt(symbol_ptr, SymEngine::integer(0))));

    if (!SymEngine::is_a<SymEngine::FiniteSet>(*soln)) {
        // Something might have gone wrong
        // TODO: log this (and introduce a logging system at all)
        return {};
    } else {
        const auto& container =
            SymEngine::down_cast<const SymEngine::FiniteSet&>(*soln).get_container();

        std::vector<Expression> ans;
        for (const auto& iter : container) {
            ans.emplace_back(iter);
        }
        return ans;
    }
}

std::vector<Expression> System::Impl::TrySolveAll(const Expression& expr, ExpressionUsedMap& used,
                                                  const SymEngine::set_basic& args) {

    auto free_symbols = SymEngine::free_symbols(expr);

    bool has_unknown_value = false;
    std::vector<Expression> ans;

    for (auto& iter : free_symbols) {
        auto& symbol = *SymEngine::rcp_static_cast<const Symbol>(iter);
        // Try to substitute a symbol
        if (args.count(iter)) // Argument
            continue;

        has_unknown_value = true;

        for (const auto& equation : equations) {
            if (used[equation] || !SymEngine::has_symbol(equation, symbol))
                continue;

            // Simplify the equation to (symbol == xxx)
            auto solns = SolveSingle(equation, symbol);

            for (const auto& soln : solns) {
                used[equation] = true;

                // Solve the (xxx) to expressions with only current free symbol or arguments
                auto new_args = free_symbols;
                for (const auto& iter2 : args) {
                    new_args.emplace(iter2);
                }
                new_args.erase(iter);
                auto solns2 = TrySolveAll(soln, used, new_args);

                for (const auto& soln2 : solns2) {
                    // Substitute and continue solving a next symbol
                    auto new_expr = expr.subs({{symbol.rcp_from_this(), soln2}});
                    const auto& solns3 = TrySolveAll(new_expr, used, args);
                    ans.insert(ans.end(), solns3.begin(), solns3.end());
                }

                used[equation] = false;
            }
        }
    }

    if (has_unknown_value) { // Cannot be solved
        return ans;
    } else { // Already done
        return {expr};
    }
}

std::vector<Expression> System::TrySolveAll(const Symbol& sym, const std::vector<Symbol>& args) {
    SymEngine::set_basic converted_args;
    for (const auto& iter : args) {
        converted_args.emplace(iter.rcp_from_this());
    }

    ExpressionUsedMap used;
    return impl->TrySolveAll(SymEngine::Expression(sym.rcp_from_this()), used, converted_args);
}

} // namespace Algebra

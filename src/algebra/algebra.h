// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <symengine/expression.h>
#include <symengine/symbol.h>

namespace Algebra {

using Expression = SymEngine::Expression;
using Symbol = SymEngine::RCP<const SymEngine::Symbol>;

class System {
public:
    explicit System();
    ~System();

    /**
     * Adds an equation to the system (expr == 0), if not already known.
     */
    void AddEquation(const Expression& expr);

    /**
     * Checks if a equation holds. i.e. whether it can be reached by the known equations.
     * @return true if the equation *always* holds, false otherwise (undetermined or never)
     */
    bool CheckEquation(const Expression& expr);

    /**
     * Try to solve a symbol, using the given symbols as arguments.
     * For example, if there are the following equations:
     * [ 3x+y = 2
     *   y+z  = 1 ]
     * `TrySolveAll(x, {z})` would return (1+z)/3.
     * `TrySolveAll(x, {y, z})` can return many expressions, like (1+z)/3, (2-y)/3, or even
     * (y+2z)/3, as long as they satisfy the conditions. NOTE, this function does not necessarily
     * return all representations.
     * `TrySolveAll(x, {})` would return an empty vector as x cannot be
     * determined without arguments.
     *
     * @param sym the Symbol to solve.
     * @param args the Symbols to use as arguments.
     * @return vector of possible representations
     */
    std::vector<Expression> TrySolveAll(const Symbol& sym, const std::vector<Symbol>& args);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace Algebra

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <symengine/expression.h>
#include <symengine/symbol.h>
#include "common/dynamic_bitset.h"

namespace Common {
class ProofChainNode;
}

namespace Algebra {

using Expression = SymEngine::Expression;
using Symbol = SymEngine::RCP<const SymEngine::Symbol>;
using ProofList = Common::DynamicBitset;

/**
 * Solves a single equation with regard to a single symbol, there are no limits
 * about what arguments to use to represent the symbol in question.
 *
 * Eg. 3x + 2y == 0 can solve to x == -2/3y (wrt x) and y == -3/2x (wrt y).
 */
std::vector<Expression> SolveSingle(const Expression& equation, const Symbol& symbol);

class System {
public:
    explicit System();
    ~System();

    /**
     * Adds an equation to the system (expr == 0), if not already known.
     */
    void AddEquation(const Expression& expr, const std::string& transform = "",
                     const std::vector<std::shared_ptr<Common::ProofChainNode>>& parents = {});

    /**
     * Checks if a equation holds. i.e. whether it can be reached by the known equations.
     * @return true if the equation *always* holds, false otherwise (undetermined or never).
     * Second element contains a list of "reasons" for this equation when result is true.
     */
    std::pair<bool, std::shared_ptr<Common::ProofChainNode>> CheckEquation(const Expression& expr);

    /**
     * Checks whether new equations have been added since the last query.
     * This clears the new_equations state.
     *
     * @return whether new equations have been added.
     */
    bool HasNewEquations();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace Algebra

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <symengine/basic.h>
#include "common/common_types.h"

namespace Algebra {

/**
 * Checks whether the sign of the expression can be confirmed, assuming that all symbols are
 * positive.
 * @return 0 if unknown, 1 if positive, -1 if negative.
 */
s8 CheckSign(const SymEngine::RCP<const SymEngine::Basic>& expr);

/**
 * Checks whether an expression is acceptable, i.e. whether it CAN be positive.
 * For example, -y-z and -x-2 are not acceptable, while x-2 and x+y-1 are.
 */
bool IsAcceptable(const SymEngine::Expression& expr);

/**
 * Simplifies an equation, removing sqrt items.
 */
SymEngine::Expression SimplifyEquation(const SymEngine::Expression& expr);

} // namespace Algebra

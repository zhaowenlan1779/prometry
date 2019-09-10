// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <utility>
#include "algebra/algebra.h"
#include "geometry/element/line.h"

namespace Core {

enum class LineDirection {
    Normal,   ///< Starting from first child point
    Reversed, ///< Starting from last child point
};

std::array<Algebra::Expression, 2> LineAngle(const std::shared_ptr<Line>& l1,
                                             const std::shared_ptr<Line>& l2);

Algebra::Expression LineAngle(const std::shared_ptr<Line>& l1, LineDirection d1,
                              const std::shared_ptr<Line>& l2, LineDirection d2);

} // namespace Core

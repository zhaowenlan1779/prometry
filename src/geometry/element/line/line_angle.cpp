// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"

namespace Core {

std::array<Algebra::Expression, 2> LineAngle(const std::shared_ptr<Line>& l1,
                                             const std::shared_ptr<Line>& l2) {
    ASSERT_MSG(!Intersection<Point>(l1, l2).empty(), "The two lines do not intersect");

    const auto& actual_l1 = std::min(l1, l2);
    const auto& actual_l2 = std::max(l1, l2);

    const auto angle = Algebra::Expression(
        SymEngine::symbol(actual_l1->Print() + "_" + actual_l2->Print() + "_angle"));
    return {angle, SymEngine::pi - angle};
}

Algebra::Expression LineAngle(const std::shared_ptr<Line>& l1, LineDirection d1,
                              const std::shared_ptr<Line>& l2, LineDirection d2) {
    if (d1 == d2) {
        return LineAngle(l1, l2).at(0);
    } else {
        return LineAngle(l1, l2).at(1);
    }
}

} // namespace Core

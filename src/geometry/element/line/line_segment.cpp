// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/line/line_segment.h"

namespace Core {

Algebra::Expression LineSegmentLength(const std::shared_ptr<Point>& p1_,
                                      const std::shared_ptr<Point>& p2_) {
    const auto& p1 = std::min(p1_, p2_);
    const auto& p2 = std::max(p1_, p2_);

    return Algebra::Expression(SymEngine::symbol(p1->Print() + p2->Print() + "_length"));
}

} // namespace Core

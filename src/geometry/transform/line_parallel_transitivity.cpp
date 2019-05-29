// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

LineParallelTransitivity::~LineParallelTransitivity() = default;

void LineParallelTransitivity::Execute(System& system, Line& l1, Line& l2, Line& l3) {

    auto c1 = l1.GetConclusion(LineParallel(l1, l2));
    auto c2 = l2.GetConclusion(LineParallel(l2, l3));
    if (c1 && c2) {
        system.AddConclusion(new LineParallel(l1, l3), "transitivity of line parallel", {c1, c2});
    }
}

} // namespace Core

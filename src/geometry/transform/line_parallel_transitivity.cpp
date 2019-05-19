// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

LineParallelTransitivity::~LineParallelTransitivity() = default;

void LineParallelTransitivity::Execute(System& system, Line& l1, Line& l2, Line& l3) {

    if (l1.HasConclusion(LineParallel(l1, l2)) && l2.HasConclusion(LineParallel(l2, l3))) {
        system.AddConclusion(new LineParallel(l1, l3));
    }
}

} // namespace Core
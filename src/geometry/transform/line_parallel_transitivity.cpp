// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

void LineParallelTransitivity::Execute(System& system, const Line& l1, const Line& l2,
                                       const Line& l3) {

    if (l1.HasConclusion(LineParallel(l1, l2)) && l2.HasConclusion(LineParallel(l2, l3))) {
        // TODO: impl
    }
}

} // namespace Core
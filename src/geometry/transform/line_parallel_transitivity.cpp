// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

LineParallelTransitivity::~LineParallelTransitivity() = default;

void LineParallelTransitivity::Execute(System& system, std::shared_ptr<Line> l1,
                                       std::shared_ptr<Line> l2, std::shared_ptr<Line> l3) {

    auto c1 = l1->GetConclusion(LineParallel(l1, l2));
    auto c2 = l2->GetConclusion(LineParallel(l2, l3));
    if (c1 && c2) {
        system.CreateConclusion<LineParallel>("transitivity of line parallel", {c1, c2}, l1, l3);
    }
}

} // namespace Core

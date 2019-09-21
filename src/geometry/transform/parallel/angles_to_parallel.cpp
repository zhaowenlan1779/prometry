// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_parallel.h"

namespace Core {

AnglesToParallel::AnglesToParallel() = default;

AnglesToParallel::~AnglesToParallel() = default;

/*static*/ void AnglesToParallel::Execute(System& system, const std::shared_ptr<Line>& l,
                                          const std::shared_ptr<Line>& l1,
                                          const std::shared_ptr<Line>& l2) {

    if (Intersection<Point>(l, l1).empty() || Intersection<Point>(l, l2).empty()) {
        return;
    }

    const auto& [ret, proof_node] = system.Algebra().CheckEquation(
        LineAngle(l, LineDirection::Normal, l1, LineDirection::Normal) -
        LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal));

    if (ret) {
        system.CreateConclusion<LineParallel>("angles to parallel", {proof_node}, l1, l2);
    }
}

} // namespace Core

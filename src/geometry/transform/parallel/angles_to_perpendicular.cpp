// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_perpendicular.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_perpendicular.h"

namespace Core {

AnglesToPerpendicular::AnglesToPerpendicular() = default;

AnglesToPerpendicular::~AnglesToPerpendicular() = default;

/*static*/ void AnglesToPerpendicular::Execute(System& system, const std::shared_ptr<Line>& l1,
                                               const std::shared_ptr<Line>& l2) {

    if (Intersection<Point>(l1, l2).empty()) {
        return;
    }

    const auto& [ret, proof_node] = system.Algebra().CheckEquation(
        LineAngle(l1, LineDirection::Normal, l2, LineDirection::Normal) -
        SymEngine::Expression(SymEngine::pi) / 2);

    if (ret) {
        system.CreateConclusion<LinePerpendicular>("angles to perpendicular", {proof_node}, l1, l2);
    }
}

} // namespace Core

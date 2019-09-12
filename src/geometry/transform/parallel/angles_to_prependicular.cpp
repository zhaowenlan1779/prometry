// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_prependicular.h"

namespace Core {

AnglesToPrependicular::AnglesToPrependicular() = default;

AnglesToPrependicular::~AnglesToPrependicular() = default;

/*static*/ void AnglesToPrependicular::Execute(System& system, const std::shared_ptr<Line>& l1,
                                               const std::shared_ptr<Line>& l2) {

    if (Intersection<Point>(l1, l2).empty()) {
        return;
    }

    if (system.Algebra().CheckEquation(
            LineAngle(l1, LineDirection::Normal, l2, LineDirection::Normal) -
            SymEngine::Expression(SymEngine::pi) / 2)) {

        system.CreateConclusion<LinePrependicular>("angles to prependicular", {}, l1, l2);
    }
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_prependicular.h"

namespace Core {

TEST_CASE("AnglesToPrependicular", "[transform]") {
    System system;
    system.RegisterTransform<AnglesToPrependicular>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto p1 = system.CreateElement<Point>("", "p1");

    p1->AddParent(l1);
    p1->AddParent(l2);

    system.Algebra().AddEquation(LineAngle(l1, LineDirection::Normal, l2, LineDirection::Normal) -
                                 SymEngine::Expression(SymEngine::pi) / 2);

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetConclusion(LinePrependicular(l1, l2)));
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/prependicular_to_angles.h"

namespace Core {

TEST_CASE("PrependicularToAngles", "[transform]") {
    System system;
    system.RegisterTransform<PrependicularToAngles>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto p1 = system.CreateElement<Point>("", "p1");
    system.CreateConclusion<LinePrependicular>("", {}, l1, l2);

    p1->AddParent(l1);
    p1->AddParent(l2);

    system.Execute([](System&) { return nullptr; });

    for (auto dir1 : {LineDirection::Normal, LineDirection::Reversed}) {
        for (auto dir2 : {LineDirection::Normal, LineDirection::Reversed}) {
            REQUIRE(system.Algebra()
                        .CheckEquation(LineAngle(l1, dir1, l2, dir2) -
                                       SymEngine::Expression(SymEngine::pi) / 2)
                        .first);
        }
    }
}

} // namespace Core

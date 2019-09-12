// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_parallel.h"

namespace Core {

TEST_CASE("AnglesToParallel", "[transform]") {
    System system;
    system.RegisterTransform<AnglesToParallel>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l = system.CreateElement<Line>("", "l");
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");

    p1->AddParent(l1);
    p1->AddParent(l);
    p2->AddParent(l2);
    p2->AddParent(l);

    SECTION("corresponding angles") {
        system.Algebra().AddEquation(
            LineAngle(l, LineDirection::Normal, l1, LineDirection::Normal) -
            LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal));

        system.Execute([](System&) { return nullptr; });

        REQUIRE(system.GetConclusion(LineParallel(l1, l2)));
    }

    SECTION("alternate interior angles") {
        system.Algebra().AddEquation(
            LineAngle(l, LineDirection::Reversed, l1, LineDirection::Reversed) -
            LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal));

        system.Execute([](System&) { return nullptr; });

        REQUIRE(system.GetConclusion(LineParallel(l1, l2)));
    }

    SECTION("interior angles on the same side") {
        system.Algebra().AddEquation(
            LineAngle(l, LineDirection::Reversed, l1, LineDirection::Normal) +
            LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal) - SymEngine::pi);

        system.Execute([](System&) { return nullptr; });

        REQUIRE(system.GetConclusion(LineParallel(l1, l2)));
    }
}

} // namespace Core

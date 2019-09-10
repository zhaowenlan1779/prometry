// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/line.h"
#include "geometry/element/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/pythagorean.h"

namespace Core {

TEST_CASE("PythagoreanSimple", "[transform]") {
    System system;
    system.RegisterTransform<Pythagorean>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    system.CreateConclusion<LinePrependicular>("", {}, l1, l2);

    p1->AddParent(l1);
    p1->AddParent(l2);
    p2->AddParent(l1);
    p3->AddParent(l2);

    // Let: AB=3 AC=4
    system.Algebra().AddEquation(LineSegmentLength(p1, p2) - SymEngine::integer(3));
    system.Algebra().AddEquation(LineSegmentLength(p1, p3) - SymEngine::integer(4));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p2, p3) - SymEngine::integer(5)));
}

} // namespace Core

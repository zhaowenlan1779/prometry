// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/pythagorean/pythagorean.h"

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

TEST_CASE("Pythagorean+LineSegmentConcat", "[transform]") {
    System system;
    system.RegisterTransform<LineSegmentConcat>();
    system.RegisterTransform<Pythagorean>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    system.CreateConclusion<LinePrependicular>("", {}, l1, l2);

    a->AddParent(l1);
    b->AddParent(l2);
    c->AddParent(l1);
    c->AddParent(l2);
    d->AddParent(l2);

    system.Algebra().AddEquation(LineSegmentLength(a, c) - 1);
    system.Algebra().AddEquation(LineSegmentLength(b, c) - 3);
    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(d, b));

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(a, d) -
                                           Algebra::Expression(5) / Algebra::Expression(3)));
}

} // namespace Core

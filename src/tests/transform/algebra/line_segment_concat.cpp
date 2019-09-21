// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/transform/algebra/line_segment_concat.h"

namespace Core {

TEST_CASE("LineSegmentConcat", "[transform]") {
    System system;
    system.RegisterTransform<LineSegmentConcat>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto p4 = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l");

    p1->AddParent(l1);
    p2->AddParent(l1);
    p3->AddParent(l1);
    p4->AddParent(l1);

    // Let: AB=3 AC=5
    system.Algebra().AddEquation(LineSegmentLength(p1, p2) - SymEngine::integer(3));
    system.Algebra().AddEquation(LineSegmentLength(p1, p3) - SymEngine::integer(5));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p2, p3) - SymEngine::integer(2)).first);

    // Let: AD=8
    system.Algebra().AddEquation(LineSegmentLength(p1, p4) - SymEngine::integer(8));

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p3, p4) - SymEngine::integer(3)).first);
    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p2, p4) - SymEngine::integer(5)).first);
}

} // namespace Core

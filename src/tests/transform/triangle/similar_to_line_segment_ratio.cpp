// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"

namespace Core {

TEST_CASE("SimilarToLineSegmentRatio", "[transform]") {
    System system;
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, f, d, e);

    // Let ABC similar FDE
    auto similar = system.CreateConclusion<TriangleSimilar>("", {}, t1, order1, t2, order2);

    system.Algebra().AddEquation(LineSegmentLength(a, b) - SymEngine::integer(3));
    system.Algebra().AddEquation(LineSegmentLength(b, c) - SymEngine::integer(4));
    system.Algebra().AddEquation(LineSegmentLength(c, a) - SymEngine::integer(5));

    system.Execute([](System& system) { return nullptr; });

    SECTION("specify the ratio") {
        system.Algebra().AddEquation(similar->GetSimilarRatio() - SymEngine::integer(2));

        REQUIRE(
            system.Algebra().CheckEquation(LineSegmentLength(d, e) - SymEngine::integer(8)).first);
        REQUIRE(
            system.Algebra().CheckEquation(LineSegmentLength(e, f) - SymEngine::integer(10)).first);
    }

    SECTION("specify a length") {
        system.Algebra().AddEquation(LineSegmentLength(f, d) - SymEngine::integer(6));

        REQUIRE(
            system.Algebra().CheckEquation(LineSegmentLength(d, e) - SymEngine::integer(8)).first);
        REQUIRE(
            system.Algebra().CheckEquation(LineSegmentLength(e, f) - SymEngine::integer(10)).first);
    }
}

// TODO: More, better tests...

} // namespace Core

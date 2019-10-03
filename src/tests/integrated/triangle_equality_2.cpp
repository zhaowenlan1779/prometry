// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/triangle/aa_similar.h"
#include "geometry/transform/triangle/isosceles_to_angles.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("TriangleEquality_2", "[integrated]") {
    System system;
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<IsoscelesToAngles>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    system.RegisterTransform<TriangleInternalAngles>();
    system.RegisterConstruction<TriangleMake>();

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");

    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, c));
    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, d));
    system.Algebra().AddEquation(LineSegmentLength(a, c) - LineSegmentLength(a, e));
    system.Algebra().AddEquation(
        LineAngle(Line::Connect(system, a, b).first, Line::Connect(system, a, d).first).at(0) -
        SymEngine::Expression(SymEngine::pi) / 2);
    system.Algebra().AddEquation(
        LineAngle(Line::Connect(system, a, c).first, Line::Connect(system, a, e).first).at(0) -
        SymEngine::Expression(SymEngine::pi) / 2);

    const auto proof1 = system.Execute([&b, &c, &d, &e](System& system) {
        const auto& [ret, proof_node] =
            system.Algebra().CheckEquation(LineSegmentLength(b, d) - LineSegmentLength(c, e));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof1 << std::endl;
    REQUIRE(!proof1.empty());

    // const auto proof2 = system.Execute([&b, &c, &d, &e](System& system) {
    //     const auto& [bd, dir1] = Line::Connect(system, b, d);
    //     const auto& [bc, dir2] = Line::Connect(system, b, c);
    //     const auto& [ret, proof_node] = system.Algebra().CheckEquation(
    //         LineAngle(bd, dir1, bc, dir2) - 23 * SymEngine::Expression(SymEngine::pi) / 36);
    //     return ret ? proof_node : nullptr;
    // });

    // std::cout << "Proof: " << proof2 << std::endl;
    // REQUIRE(!proof2.empty());
}

} // namespace Core

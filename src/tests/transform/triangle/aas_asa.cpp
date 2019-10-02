// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/aa_similar.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("AAS_Equality", "[transform]") {
    System system;
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, d, e, f);

    // Let: A=60 (pi/3), B=30 (pi/6), a = 4
    std::array<Algebra::Expression, 3> angles_1{{t1->angle_A, t1->angle_B, t1->angle_C}};
    ApplyTransform(order1, angles_1);
    system.Algebra().AddEquation(angles_1[0] - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(angles_1[1] - SymEngine::Expression(SymEngine::pi) / 6);

    std::array<Algebra::Expression, 3> edges_1{{t1->length_a, t1->length_b, t1->length_c}};
    ApplyTransform(order1, edges_1);
    system.Algebra().AddEquation(edges_1[0] - SymEngine::integer(4));

    // Let: D=30 (pi/6), F=60 (pi/2), f = 4
    std::array<Algebra::Expression, 3> angles_2{{t2->angle_A, t2->angle_B, t2->angle_C}};
    ApplyTransform(order2, angles_2);
    system.Algebra().AddEquation(angles_2[0] - SymEngine::Expression(SymEngine::pi) / 6);
    system.Algebra().AddEquation(angles_2[2] - SymEngine::Expression(SymEngine::pi) / 3);

    std::array<Algebra::Expression, 3> edges_2{{t2->length_a, t2->length_b, t2->length_c}};
    ApplyTransform(order2, edges_2);
    system.Algebra().AddEquation(edges_2[2] - SymEngine::integer(4));

    system.Execute([](System& system) { return nullptr; });

    const auto order3 = MakeTriangle(system, f, d, e).second;

    auto similar = std::dynamic_pointer_cast<TriangleSimilar>(
        system.GetConclusion(TriangleSimilar(t1, order1, t2, order3)));
    REQUIRE(similar != nullptr);
    REQUIRE(system.Algebra().CheckEquation(similar->GetSimilarRatio() - 1).first);
}

TEST_CASE("ASA_Equality", "[transform]") {
    System system;
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, d, e, f);

    // Let: A=60 (pi/3), B=30 (pi/6), c = 5
    std::array<Algebra::Expression, 3> angles_1{{t1->angle_A, t1->angle_B, t1->angle_C}};
    ApplyTransform(order1, angles_1);
    system.Algebra().AddEquation(angles_1[0] - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(angles_1[1] - SymEngine::Expression(SymEngine::pi) / 6);

    std::array<Algebra::Expression, 3> edges_1{{t1->length_a, t1->length_b, t1->length_c}};
    ApplyTransform(order1, edges_1);
    system.Algebra().AddEquation(edges_1[2] - SymEngine::integer(5));

    // Let: D=30 (pi/6), F=60 (pi/2), e = 5
    std::array<Algebra::Expression, 3> angles_2{{t2->angle_A, t2->angle_B, t2->angle_C}};
    ApplyTransform(order2, angles_2);
    system.Algebra().AddEquation(angles_2[0] - SymEngine::Expression(SymEngine::pi) / 6);
    system.Algebra().AddEquation(angles_2[2] - SymEngine::Expression(SymEngine::pi) / 3);

    std::array<Algebra::Expression, 3> edges_2{{t2->length_a, t2->length_b, t2->length_c}};
    ApplyTransform(order2, edges_2);
    system.Algebra().AddEquation(edges_2[1] - SymEngine::integer(5));

    system.Execute([](System& system) { return nullptr; });

    const auto order3 = MakeTriangle(system, f, d, e).second;

    auto similar = std::dynamic_pointer_cast<TriangleSimilar>(
        system.GetConclusion(TriangleSimilar(t1, order1, t2, order3)));
    REQUIRE(similar != nullptr);
    REQUIRE(system.Algebra().CheckEquation(similar->GetSimilarRatio() - 1).first);
}

} // namespace Core

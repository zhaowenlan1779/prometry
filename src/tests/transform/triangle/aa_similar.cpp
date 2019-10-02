// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/aa_similar.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("AASimilar", "[transform]") {
    System system;
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, d, e, f);

    // Let: A=60 (pi/3), B=30 (pi/6)
    std::array<Algebra::Expression, 3> angles_1{{t1->angle_A, t1->angle_B, t1->angle_C}};
    ApplyTransform(order1, angles_1);
    system.Algebra().AddEquation(angles_1[0] - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(angles_1[1] - SymEngine::Expression(SymEngine::pi) / 6);

    // Let: D=30 (pi/6), E=90 (pi/2)
    std::array<Algebra::Expression, 3> angles_2{{t2->angle_A, t2->angle_B, t2->angle_C}};
    ApplyTransform(order2, angles_2);
    system.Algebra().AddEquation(angles_2[0] - SymEngine::Expression(SymEngine::pi) / 6);
    system.Algebra().AddEquation(angles_2[1] - SymEngine::Expression(SymEngine::pi) / 2);

    system.Execute([](System& system) { return nullptr; });

    const auto order3 = MakeTriangle(system, f, d, e).second;

    REQUIRE(system.GetConclusion(TriangleSimilar(t1, order1, t2, order3)) != nullptr);
}

// TODO: More, better tests...

} // namespace Core

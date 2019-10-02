// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/isosceles_to_angles.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("IsoscelesToAngles", "[transform]") {
    System system;
    system.RegisterTransform<IsoscelesToAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->length_a - triangle->length_b);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(triangle->angle_A - triangle->angle_B).first);
}

TEST_CASE("IsoscelesToAngles[EquilateralTriangle]", "[transform]") {
    System system;
    system.RegisterTransform<IsoscelesToAngles>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->length_a - SymEngine::integer(3));
    system.Algebra().AddEquation(triangle->length_b - SymEngine::integer(3));
    system.Algebra().AddEquation(triangle->length_c - SymEngine::integer(3));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_A - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_B - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_C - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
}

} // namespace Core

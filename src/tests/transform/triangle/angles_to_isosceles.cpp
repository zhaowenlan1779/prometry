// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/angles_to_isosceles.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("AnglesToIsosceles", "[transform]") {
    System system;
    system.RegisterTransform<AnglesToIsosceles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->angle_A - triangle->angle_B);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(triangle->length_a - triangle->length_b).first);
}

TEST_CASE("AnglesToIsosceles[EquilateralTriangle]", "[transform]") {
    System system;
    system.RegisterTransform<AnglesToIsosceles>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->angle_A - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(triangle->angle_B - SymEngine::Expression(SymEngine::pi) / 3);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(triangle->length_a - triangle->length_b).first);
    REQUIRE(system.Algebra().CheckEquation(triangle->length_b - triangle->length_c).first);
}

} // namespace Core

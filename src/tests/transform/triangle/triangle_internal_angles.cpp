// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("TriangleInternalAngles", "[transform]") {
    System system;
    system.RegisterTransform<TriangleInternalAngles>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto t = system.CreateElement<Triangle>("", system, p1, p2, p3);

    // Let: A=60 (pi/3), B=30 (pi/6)
    system.Algebra().AddEquation(t->angle_A - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(t->angle_B - SymEngine::Expression(SymEngine::pi) / 6);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(t->angle_C - SymEngine::Expression(SymEngine::pi) / 2).first);
}

// TODO: More, better tests...

} // namespace Core

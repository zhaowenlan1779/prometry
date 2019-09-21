// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("TriangleMake", "[construction]") {
    System system;
    system.RegisterConstruction<TriangleMake>();
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");
    auto p4 = system.CreateElement<Point>("", "p4");
    auto p5 = system.CreateElement<Point>("", "p5");

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetElements(Elements::Triangle).size() == 10);
}

} // namespace Core

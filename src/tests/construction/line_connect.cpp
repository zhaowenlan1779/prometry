// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/line_connect.h"
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("LineConnect", "[construction]") {
    System system;
    system.RegisterConstruction<LineConnect>();
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetElements(Elements::Line).size() == 3);
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/line_connect.h"
#include "geometry/element/line.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("LineConnect", "[construction]") {
    System system;
    system.RegisterConstruction<LineConnect>();
    Point* p1 = new Point("A");
    Point* p2 = new Point("B");
    Point* p3 = new Point("C");
    system.AddElement(p1);
    system.AddElement(p2);
    system.AddElement(p3);

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetElement<Line>().size() == 3);
}

} // namespace Core
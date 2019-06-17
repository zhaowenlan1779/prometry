// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/element.h"
#include "core/system.h"
#include "geometry/element/line.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("ElementIntersection", "[core]") {
    System system;
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");

    p1->AddParent(l1);
    p1->AddParent(l2);
    p1->AddParent(l3);
    p2->AddParent(l1);
    p2->AddParent(l3);
    p3->AddParent(l2);

#define REQUIRE_CONTAINS(a, b) REQUIRE(std::find(a.begin(), a.end(), (b)) != a.end())

    {
        auto ans = Intersection<Point>(l1, l3);
        REQUIRE(ans.size() == 2);
        REQUIRE_CONTAINS(ans, p1);
        REQUIRE_CONTAINS(ans, p2);
    }

    {
        auto ans = Intersection<Point>(l1, l2);
        REQUIRE(ans.size() == 1);
        REQUIRE_CONTAINS(ans, p1);
    }

    {
        auto ans = Intersection<Point>(l2, l3);
        REQUIRE(ans.size() == 1);
        REQUIRE_CONTAINS(ans, p1);
    }

    {
        auto ans = Intersection<Point>(l1, l2, l3);
        REQUIRE(ans.size() == 1);
        REQUIRE_CONTAINS(ans, p1);
    }

    {
        auto ans = Intersection<Line>(l1, l3);
        REQUIRE(ans.size() == 0);
    }

#undef REQUIRE_CONTAINS
}

} // namespace Core

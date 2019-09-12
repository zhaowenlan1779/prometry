// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/element.h"
#include "core/system.h"
#include "geometry/element/line/line.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("ElementCommonParent", "[core]") {
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
        auto ans = CommonParent<Line>(p1, p2);
        REQUIRE(ans.size() == 2);
        REQUIRE_CONTAINS(ans, l1);
        REQUIRE_CONTAINS(ans, l3);
    }

    {
        auto ans = CommonParent<Line>(p1, p3);
        REQUIRE(ans.size() == 1);
        REQUIRE_CONTAINS(ans, l2);
    }

    {
        auto ans = CommonParent<Line>(p2, p3);
        REQUIRE(ans.size() == 0);
    }

    {
        auto ans = CommonParent<Line>(p1, p2, p3);
        REQUIRE(ans.size() == 0);
    }

    {
        auto ans = CommonParent<Point>(p1, p2);
        REQUIRE(ans.size() == 0);
    }

#undef REQUIRE_CONTAINS
}

} // namespace Core

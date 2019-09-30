// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"

namespace Core {

TEST_CASE("RelativeTriangleOrder", "[element]") {
    for (std::size_t i = 0; i < TriangleOrders::Count; ++i) {
        for (std::size_t j = 0; j < TriangleOrders::Count; ++j) {
            std::array<int, 3> order1{{0, 1, 2}};
            ApplyTransform(TriangleOrder(i), order1);
            const auto new_transform = GetRelativeTriangleOrder(TriangleOrder(i), TriangleOrder(j));
            ApplyTransform(new_transform, order1);

            std::array<int, 3> order2{{0, 1, 2}};
            ApplyTransform(TriangleOrder(j), order2);

            REQUIRE(order1 == order2);
        }
    }
}

TEST_CASE("CombineTriangleOrder", "[element]") {
    for (std::size_t i = 0; i < TriangleOrders::Count; ++i) {
        for (std::size_t j = 0; j < TriangleOrders::Count; ++j) {
            std::array<int, 3> order1{{0, 1, 2}};
            ApplyTransform(TriangleOrder(i), order1);
            ApplyTransform(TriangleOrder(j), order1);

            std::array<int, 3> order2{{0, 1, 2}};
            ApplyTransform(CombineTriangleOrder(TriangleOrder(i), TriangleOrder(j)), order2);

            REQUIRE(order1 == order2);
        }
    }
}

TEST_CASE("MakeTriangle", "[element]") {
    System system;
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");
    auto t = system.CreateElement<Triangle>("", system, p1, p2, p3);

    std::array<std::shared_ptr<Point>, 3> target{{t->A, t->B, t->C}};

#define CHECK_ORDER(p1, p2, p3)                                                                    \
    {                                                                                              \
        std::array<std::shared_ptr<Point>, 3> cur{{t->A, t->B, t->C}};                             \
        const auto& [triangle, order] = MakeTriangle(system, p1, p2, p3);                          \
        REQUIRE(triangle == t);                                                                    \
        ApplyTransform(order, cur);                                                                \
        REQUIRE((cur[0] == p1 && cur[1] == p2 && cur[2] == p3));                                   \
    }

    {
        using namespace TriangleOrders;
        CHECK_ORDER(p1, p2, p3);
        CHECK_ORDER(p1, p3, p2);
        CHECK_ORDER(p2, p1, p3);
        CHECK_ORDER(p2, p3, p1);
        CHECK_ORDER(p3, p1, p2);
        CHECK_ORDER(p3, p2, p1);
    }
#undef CHECK_ORDER
}

} // namespace Core

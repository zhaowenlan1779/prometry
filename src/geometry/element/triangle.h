// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include "core/element.h"

namespace Core {

class Point;
class Line;
class System;

class Triangle : public Element {
public:
    static ElementType Type;

    explicit Triangle(System& system, const std::shared_ptr<Point>& A,
                      const std::shared_ptr<Point>& B, const std::shared_ptr<Point>& C);
    ~Triangle() override;
    std::string GetName() const override;
    std::string GetFullname() const override;
    ElementType GetType() const override;
    u64 GetHash() const override;

    std::shared_ptr<Point> A, B, C;
    std::shared_ptr<Line> a, b, c;
    Algebra::Expression angle_A, angle_B, angle_C;
    Algebra::Expression length_a, length_b, length_c;
};

namespace TriangleOrders {
enum TriangleOrder {
    ABC,
    ACB,
    BAC,
    BCA,
    CAB,
    CBA,
    Count,
};
}

using TriangleOrders::TriangleOrder;

/// Map of transforms for the triangle orders
static constexpr std::array<std::array<int, 3>, 6> OrderTransforms{{
    {0, 1, 2},
    {0, 2, 1},
    {1, 0, 2},
    {1, 2, 0},
    {2, 0, 1},
    {2, 1, 0},
}};

template <typename T>
void ApplyTransform(TriangleOrder order, std::array<T, 3>& cur) {
    std::array<T, 3> nxt;
    for (std::size_t i = 0; i < nxt.size(); ++i) {
        nxt[i] = cur[OrderTransforms[order][i]];
    }
    cur = nxt;
}

/// Get the relative order of B to A. E.g. ACB to ACB is ABC.
TriangleOrder GetRelativeTriangleOrder(TriangleOrder a, TriangleOrder b);

/**
 * Finds a triangle, constructing one if not exist, and returns
 * the relative order of P1 P2 P3 to it.
 */
std::pair<std::shared_ptr<Triangle>, TriangleOrder> MakeTriangle(System& system,
                                                                 const std::shared_ptr<Point>& p1,
                                                                 const std::shared_ptr<Point>& p2,
                                                                 const std::shared_ptr<Point>& p3);

} // namespace Core

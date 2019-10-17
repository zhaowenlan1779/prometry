// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "core/system.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"

namespace Core {

/*static*/ ElementType Triangle::Type = Elements::Triangle;

ElementType Triangle::GetType() const {
    return Triangle::Type;
}

Triangle::Triangle(System& system, const std::shared_ptr<Point>& A_,
                   const std::shared_ptr<Point>& B_, const std::shared_ptr<Point>& C_) {
    std::array<std::shared_ptr<Point>, 3> points = {A_, B_, C_};
    std::sort(points.begin(), points.end());
    A = std::move(points[0]);
    B = std::move(points[1]);
    C = std::move(points[2]);
    a = Line::Connect(system, B, C).first;
    b = Line::Connect(system, A, C).first;
    c = Line::Connect(system, A, B).first;
    length_a = LineSegmentLength(B, C);
    length_b = LineSegmentLength(A, C);
    length_c = LineSegmentLength(A, B);
    angle_A = LineAngle(b, b->GetLineDirection(A, C), c, c->GetLineDirection(A, B));
    angle_B = LineAngle(a, a->GetLineDirection(B, C), c, c->GetLineDirection(B, A));
    angle_C = LineAngle(b, b->GetLineDirection(C, A), a, a->GetLineDirection(C, B));
}

Triangle::~Triangle() = default;

std::string Triangle::Print(PrintFormat format) const {
    const auto name = A->Print(format) + B->Print(format) + C->Print(format);
    if (format == PrintFormat::Plain) {
        return "Triangle " + name;
    } else if (format == PrintFormat::Latex) {
        return "\\bigtriangleup " + name;
    }

    UNREACHABLE_MSG("Unexpected format!");
}

u64 Triangle::GetHash() const {
    return std::hash<std::string>()(Print());
}

TriangleOrder GetRelativeTriangleOrder(TriangleOrder a, TriangleOrder b) {
    using namespace TriangleOrders;
    /// Map for quick lookup
    static constexpr std::array<std::array<TriangleOrder, Count>, Count> TriangleOrderMap = {{
        {/* ABC */ {ABC, ACB, BAC, BCA, CAB, CBA}},
        {/* ACB */ {ACB, ABC, CAB, CBA, BAC, BCA}},
        {/* BAC */ {BAC, BCA, ABC, ACB, CBA, CAB}},
        {/* BCA */ {CAB, CBA, ACB, ABC, BCA, BAC}},
        {/* CAB */ {BCA, BAC, CBA, CAB, ABC, ACB}},
        {/* CBA */ {CBA, CAB, BCA, BAC, ACB, ABC}},
    }};

    return TriangleOrderMap[a][b];
}

TriangleOrder InverseTriangleOrder(TriangleOrder order) {
    return GetRelativeTriangleOrder(order, TriangleOrders::ABC);
}

TriangleOrder CombineTriangleOrder(TriangleOrder a, TriangleOrder b) {
    using namespace TriangleOrders;
    /// Map for quick lookup
    static constexpr std::array<std::array<TriangleOrder, Count>, Count> TriangleOrderMap = {{
        {/* ABC */ {ABC, ACB, BAC, BCA, CAB, CBA}},
        {/* ACB */ {ACB, ABC, CAB, CBA, BAC, BCA}},
        {/* BAC */ {BAC, BCA, ABC, ACB, CBA, CAB}},
        {/* BCA */ {BCA, BAC, CBA, CAB, ABC, ACB}},
        {/* CAB */ {CAB, CBA, ACB, ABC, BCA, BAC}},
        {/* CBA */ {CBA, CAB, BCA, BAC, ACB, ABC}},
    }};

    return TriangleOrderMap[a][b];
}

std::pair<std::shared_ptr<Triangle>, TriangleOrder> MakeTriangle(System& system,
                                                                 const std::shared_ptr<Point>& p1,
                                                                 const std::shared_ptr<Point>& p2,
                                                                 const std::shared_ptr<Point>& p3) {
    const auto& t = system.CreateElement<Triangle>(
        "Make triangle " + p1->Print() + p2->Print() + p3->Print(), system, p1, p2, p3);

    const std::array<std::pair<TriangleOrder, std::array<std::shared_ptr<Point>, 3>>, 6>
        PointsOrderMap{{
            {TriangleOrders::ABC, {t->A, t->B, t->C}},
            {TriangleOrders::ACB, {t->A, t->C, t->B}},
            {TriangleOrders::BAC, {t->B, t->A, t->C}},
            {TriangleOrders::BCA, {t->B, t->C, t->A}},
            {TriangleOrders::CAB, {t->C, t->A, t->B}},
            {TriangleOrders::CBA, {t->C, t->B, t->A}},
        }};
    const std::array<std::shared_ptr<Point>, 3> current_order{{p1, p2, p3}};

    for (const auto& [triangle_order, points_order] : PointsOrderMap) {
        if (points_order == current_order) {
            return {t, triangle_order};
        }
    }

    UNREACHABLE();
}

} // namespace Core

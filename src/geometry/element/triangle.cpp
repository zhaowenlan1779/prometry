// Copyright 2019 Zhupengfei and others
// All rights reserved.

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
    a = Line::Connect(system, B, C);
    b = Line::Connect(system, A, C);
    c = Line::Connect(system, A, B);
    length_a = LineSegmentLength(B, C);
    length_b = LineSegmentLength(A, C);
    length_c = LineSegmentLength(A, B);
    angle_A = LineAngle(b, b->GetLineDirection(A, C), c, c->GetLineDirection(A, B));
    angle_B = LineAngle(a, a->GetLineDirection(B, C), c, c->GetLineDirection(B, A));
    angle_C = LineAngle(b, b->GetLineDirection(C, A), a, a->GetLineDirection(C, B));
}

Triangle::~Triangle() = default;

std::string Triangle::GetName() const {
    return A->GetName() + B->GetName() + C->GetName();
}

std::string Triangle::GetFullname() const {
    return "Triangle " + GetName();
}

u64 Triangle::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

} // namespace Core

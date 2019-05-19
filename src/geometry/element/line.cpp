// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/line.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Line::Type = 2;

Line::Line(const Point& p1_, const Point& p2_) : p1(p1_), p2(p2_) {}

Line::~Line() = default;

std::string Line::GetName() const {
    return p1.GetName() + p2.GetName();
}

std::string Line::GetFullname() const {
    return "Line " + GetName();
}

ElementType Line::GetType() const {
    return Line::Type;
}

u64 Line::GetHash() const {
    return (p1.GetHash() + p2.GetHash()) * 97 + 1;
}

} // namespace Core
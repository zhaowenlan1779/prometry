// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/element_types.h"
#include "geometry/element/line.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Line::Type = Elements::Line;

ElementType Line::GetType() const {
    return Line::Type;
}

TwoPointsLine::TwoPointsLine(const Point& p1_, const Point& p2_) : p1(p1_), p2(p2_) {}

TwoPointsLine::~TwoPointsLine() = default;

std::string TwoPointsLine::GetName() const {
    return p1.GetName() + p2.GetName();
}

std::string TwoPointsLine::GetFullname() const {
    return "Line " + GetName();
}

u64 TwoPointsLine::GetHash() const {
    return (p1.GetHash() + p2.GetHash()) * 97 + 1;
}

StandaloneLine::StandaloneLine(const std::string& name_) : name(name_) {}

StandaloneLine::~StandaloneLine() = default;

std::string StandaloneLine::GetName() const {
    return name;
}

std::string StandaloneLine::GetFullname() const {
    return "SLine " + name;
}

u64 StandaloneLine::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

} // namespace Core
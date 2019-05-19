// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Point::Type = Elements::Point;

Point::Point(const std::string& name_) : name(name_) {}

Point::~Point() = default;

std::string Point::GetName() const {
    return name;
}

std::string Point::GetFullname() const {
    return "Point " + name;
}

ElementType Point::GetType() const {
    return Point::Type;
}

u64 Point::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

} // namespace Core
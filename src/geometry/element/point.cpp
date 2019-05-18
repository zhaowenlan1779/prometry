// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/point.h"

namespace Core {

Point::Point(const std::string& name_) : name(name_) {}

std::string Point::GetName() const {
    return name;
}

std::string Point::GetFullname() const {
    return "Point " + name;
}

u64 Point::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

} // namespace Core
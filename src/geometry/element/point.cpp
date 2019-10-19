// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Point::Type = Elements::Point;

Point::Point(const std::string& name_) : name(name_) {}

Point::~Point() = default;

std::string Point::Print(Common::PrintFormat format) const {
    if (format == Common::PrintFormat::Plain) {
        return name;
    } else if (format == Common::PrintFormat::Latex) {
        return name;
    }

    UNREACHABLE_MSG("Unexpected format!");
}

ElementType Point::GetType() const {
    return Point::Type;
}

u64 Point::GetHash() const {
    return std::hash<std::string>()("Point " + Print());
}

} // namespace Core

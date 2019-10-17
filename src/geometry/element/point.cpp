// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Point::Type = Elements::Point;

Point::Point(const std::string& name_) : name(name_) {}

Point::~Point() = default;

std::string Point::Print(PrintFormat format) const {
    if (format == PrintFormat::Plain) {
        return "Point " + name;
    } else if (format == PrintFormat::Latex) {
        return name;
    }

    UNREACHABLE_MSG("Unexpected format!");
}

ElementType Point::GetType() const {
    return Point::Type;
}

u64 Point::GetHash() const {
    return std::hash<std::string>()(Print());
}

} // namespace Core

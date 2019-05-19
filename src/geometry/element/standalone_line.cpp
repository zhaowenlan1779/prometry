// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/element/element_types.h"
#include "geometry/element/standalone_line.h"

namespace Core {

/*static*/ ElementType StandaloneLine::Type = Elements::Line;

StandaloneLine::StandaloneLine(const std::string& name_) : name(name_) {}

StandaloneLine::~StandaloneLine() = default;

std::string StandaloneLine::GetName() const {
    return name;
}

std::string StandaloneLine::GetFullname() const {
    return "SLine " + name;
}

ElementType StandaloneLine::GetType() const {
    return StandaloneLine::Type;
}

u64 StandaloneLine::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

} // namespace Core

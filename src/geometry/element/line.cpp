// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/system.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Line::Type = Elements::Line;

ElementType Line::GetType() const {
    return Line::Type;
}

Line::Line(const std::string& name_) : name(name_) {}

Line::~Line() = default;

std::string Line::GetName() const {
    return name;
}

std::string Line::GetFullname() const {
    return "Line " + name;
}

u64 Line::GetHash() const {
    return std::hash<std::string>()(GetFullname());
}

/*static*/ std::shared_ptr<Line> Line::Connect(System& system, const std::shared_ptr<Point>& p1,
                                               const std::shared_ptr<Point>& p2) {
    auto lines = Core::CommonParent<Line>(p1, p2);
    if (lines.empty()) {
        auto line = system.CreateElement<Line>("Connect " + p1->GetName() + p2->GetName(),
                                               p1->GetName() + p2->GetName());
        p1->AddParent(line);
        p2->AddParent(line);
        return line;
    } else {
        return std::dynamic_pointer_cast<Line>(*lines.begin());
    }
}

} // namespace Core

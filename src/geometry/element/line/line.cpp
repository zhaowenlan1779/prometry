// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "core/system.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Line::Type = Elements::Line;

ElementType Line::GetType() const {
    return Line::Type;
}

Line::Line(const std::string& name_) : name(name_) {}

Line::~Line() = default;

std::string Line::Print(Common::PrintFormat format) const {
    if (format == Common::PrintFormat::Plain) {
        return name;
    } else if (format == Common::PrintFormat::Latex) {
        return name;
    }

    UNREACHABLE_MSG("Unexpected format!");
}

u64 Line::GetHash() const {
    return std::hash<std::string>()("Line " + Print());
}

LineDirection Line::GetLineDirection(const std::shared_ptr<Point>& p1,
                                     const std::shared_ptr<Point>& p2) const {
    ASSERT(children.count(Elements::Point));
    for (const auto& iter : children.at(Elements::Point)) {
        if (iter.lock()->GetHash() == p1->GetHash()) {
            return LineDirection::Normal;
        }
        if (iter.lock()->GetHash() == p2->GetHash()) {
            return LineDirection::Reversed;
        }
    }
    UNREACHABLE();
}

/*static*/ std::pair<std::shared_ptr<Line>, LineDirection> Line::Connect(
    System& system, const std::shared_ptr<Point>& p1, const std::shared_ptr<Point>& p2) {
    auto lines = Core::CommonParent<Line>(p1, p2);
    if (lines.empty()) {
        const auto statement = "Connect " + Common::StringPack{/*Plain*/ "", /*Latex*/ "\\("} +
                               p1->PrintAll() + p2->PrintAll() +
                               Common::StringPack{/*Plain*/ "", /*Latex*/ "\\)"};
        auto line = system.CreateElement<Line>(statement, p1->Print() + p2->Print());
        p1->AddParent(line);
        p2->AddParent(line);
        return {line, line->GetLineDirection(p1, p2)};
    } else {
        const auto& line = std::dynamic_pointer_cast<Line>(*lines.begin());
        return {line, line->GetLineDirection(p1, p2)};
    }
}

} // namespace Core

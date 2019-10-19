// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/triangle.h"

namespace Core {

TriangleMake::~TriangleMake() = default;

void TriangleMake::Execute(System& system, const std::shared_ptr<Point>& p1,
                           const std::shared_ptr<Point>& p2, const std::shared_ptr<Point>& p3) {

    if (!CommonParent<Line>(p1, p2, p3).empty()) {
        return;
    }

    const auto statement =
        "Declare " + Common::StringPack{/*Plain*/ "Triangle", /*Latex*/ "\\(\\bigtriangleup"} +
        " " + p1->PrintAll() + p2->PrintAll() + p3->PrintAll() +
        Common::StringPack{/*Plain*/ "", /*Latex*/ "\\)"};
    system.CreateElement<Triangle>(statement, system, p1, p2, p3);
}

} // namespace Core

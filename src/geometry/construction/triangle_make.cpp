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

    system.CreateElement<Triangle>("Declare Triangle " + p1->Print() + "_" + p2->Print() + "_" +
                                       p3->Print(),
                                   system, p1, p2, p3);
}

} // namespace Core

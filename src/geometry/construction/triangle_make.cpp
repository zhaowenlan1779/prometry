// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/construction/triangle_make.h"
#include "geometry/element/triangle.h"

namespace Core {

TriangleMake::~TriangleMake() = default;

void TriangleMake::Execute(System& system, const std::shared_ptr<Point>& p1,
                           const std::shared_ptr<Point>& p2, const std::shared_ptr<Point>& p3) {

    system.CreateElement<Triangle>("Declare Triangle " + p1->GetName() + "_" + p2->GetName() + "_" +
                                       p3->GetName(),
                                   system, p1, p2, p3);
}

} // namespace Core

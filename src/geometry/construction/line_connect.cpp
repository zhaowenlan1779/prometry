// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/construction/line_connect.h"
#include "geometry/element/line.h"

namespace Core {

LineConnect::~LineConnect() = default;

void LineConnect::Execute(System& system, Point& p1, Point& p2) {

    system.AddElement(new TwoPointsLine(p1, p2), "Connect " + p1.GetName() + p2.GetName());
}

} // namespace Core
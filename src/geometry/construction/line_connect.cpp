// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/construction/line_connect.h"
#include "geometry/element/line/line.h"

namespace Core {

LineConnect::~LineConnect() = default;

void LineConnect::Execute(System& system, const std::shared_ptr<Point>& p1,
                          const std::shared_ptr<Point>& p2) {

    // This creates the line when necessary
    Line::Connect(system, p1, p2);
}

} // namespace Core

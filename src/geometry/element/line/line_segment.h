// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "algebra/algebra.h"
#include "geometry/element/point.h"

namespace Core {

Algebra::Expression LineSegmentLength(const std::shared_ptr<Point>& p1,
                                      const std::shared_ptr<Point>& p2);

} // namespace Core

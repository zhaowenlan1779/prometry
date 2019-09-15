// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/point.h"

namespace Core {

class System;

class TriangleMake : public Wrapper<TriangleMake, Point, Point, Point> {
public:
    ~TriangleMake() override;

    static void Execute(System& system, const std::shared_ptr<Point>& p1,
                        const std::shared_ptr<Point>& p2, const std::shared_ptr<Point>& p3);
};

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/point.h"

namespace Core {

class System;

class LineConnect : public Wrapper<LineConnect, Point, Point> {
public:
    ~LineConnect() override;

    static void Execute(System& system, Point& p1, Point& p2);
};

}
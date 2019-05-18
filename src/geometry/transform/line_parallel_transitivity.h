// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/line.h"

namespace Core {

class System;

class LineParallelTransitivity : public Wrapper<LineParallelTransitivity, Line, Line, Line> {
public:
    static void Execute(System& system, const Line& l1, const Line& l2, const Line& l3);
};

}
// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/line.h"

namespace Core {

class System;

class LineParallelTransitivity : public Wrapper<LineParallelTransitivity, Line, Line, Line> {
public:
    ~LineParallelTransitivity() override;
    std::string GetName() const override;

    static void Execute(System& system, Line& l1, Line& l2, Line& l3);
};

}
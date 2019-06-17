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

    static void Execute(System& system, std::shared_ptr<Line> l1, std::shared_ptr<Line> l2,
                        std::shared_ptr<Line> l3);
};

} // namespace Core
// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/line.h"

namespace Core {

class System;

class LineSegmentConcat : public Wrapper<LineSegmentConcat, Line> {
public:
    explicit LineSegmentConcat();
    ~LineSegmentConcat() override;

    static void Execute(System& system, const std::shared_ptr<Line>& line);
};

} // namespace Core

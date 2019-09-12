// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/line/line.h"

namespace Core {

class System;

class AnglesToParallel : public Wrapper<AnglesToParallel, Line, Line, Line> {
public:
    explicit AnglesToParallel();
    ~AnglesToParallel() override;

    static void Execute(System& system, const std::shared_ptr<Line>& l,
                        const std::shared_ptr<Line>& l1, const std::shared_ptr<Line>& l2);
};

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"

namespace Core {

class System;

class LineParallelTransitivity : public Transform {
public:
    explicit LineParallelTransitivity();
    ~LineParallelTransitivity() override;

    void Execute(System& system);
};

} // namespace Core

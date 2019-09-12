// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"

namespace Core {

class System;

class ParallelToAngles : public Transform {
public:
    explicit ParallelToAngles();
    ~ParallelToAngles() override;

    void Execute(System& system);
};

} // namespace Core

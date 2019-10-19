// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"

namespace Core {

class System;

class PerpendicularToAngles : public Transform {
public:
    explicit PerpendicularToAngles();
    ~PerpendicularToAngles() override;

    void Execute(System& system);
};

} // namespace Core

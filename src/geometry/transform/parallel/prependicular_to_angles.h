// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"

namespace Core {

class System;

class PrependicularToAngles : public Transform {
public:
    explicit PrependicularToAngles();
    ~PrependicularToAngles() override;

    void Execute(System& system);
};

} // namespace Core

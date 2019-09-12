// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"

namespace Core {

class System;

class Pythagorean : public Transform {
public:
    explicit Pythagorean();
    ~Pythagorean() override;

    void Execute(System& system);
};

} // namespace Core

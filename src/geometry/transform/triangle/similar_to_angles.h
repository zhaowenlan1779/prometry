// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class SimilarToAngles : public Transform {
public:
    explicit SimilarToAngles();
    ~SimilarToAngles() override;

    void Execute(System& system);
};

} // namespace Core

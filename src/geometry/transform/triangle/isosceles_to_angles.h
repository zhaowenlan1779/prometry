// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class IsoscelesToAngles : public Wrapper<IsoscelesToAngles, Triangle> {
public:
    explicit IsoscelesToAngles();
    ~IsoscelesToAngles() override;

    static void Execute(System& system, const std::shared_ptr<Triangle>& t);
};

} // namespace Core

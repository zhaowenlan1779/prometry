// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class AnglesToIsosceles : public Wrapper<AnglesToIsosceles, Triangle> {
public:
    explicit AnglesToIsosceles();
    ~AnglesToIsosceles() override;

    static void Execute(System& system, const std::shared_ptr<Triangle>& t);
};

} // namespace Core

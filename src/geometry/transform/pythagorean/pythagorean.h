// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class Pythagorean : public Wrapper<Pythagorean, Triangle> {
public:
    explicit Pythagorean();
    ~Pythagorean() override;

    static void Execute(System& system, const std::shared_ptr<Triangle>& t);
};

} // namespace Core

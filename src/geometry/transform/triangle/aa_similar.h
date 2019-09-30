// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class AASimilar : public Wrapper<AASimilar, Triangle, Triangle> {
public:
    explicit AASimilar();
    ~AASimilar() override;

    static void Execute(System& system, const std::shared_ptr<Triangle>& t1,
                        const std::shared_ptr<Triangle>& t2);
};

} // namespace Core

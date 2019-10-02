// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/transform.h"
#include "geometry/element/triangle.h"

namespace Core {

class System;

class SSS_Similar : public Wrapper<SSS_Similar, Triangle, Triangle> {
public:
    explicit SSS_Similar();
    ~SSS_Similar() override;

    static void Execute(System& system, const std::shared_ptr<Triangle>& t1,
                        const std::shared_ptr<Triangle>& t2);
};

} // namespace Core

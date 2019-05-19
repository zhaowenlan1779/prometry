// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/system.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

/// Registers all the transforms available currently.
void RegisterAllTransforms(System& system) {
    system.RegisterTransform<LineParallelTransitivity>();
}

}
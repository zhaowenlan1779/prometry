// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/system.h"
#include "geometry/construction/line_connect.h"

namespace Core {

/// Registers all the constructions available currently.
void RegisterAllConstructions(System& system) {
    system.RegisterConstruction<LineConnect>();
}

}
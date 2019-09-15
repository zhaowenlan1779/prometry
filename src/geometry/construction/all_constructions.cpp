// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/system.h"
#include "geometry/construction/all_constructions.h"
#include "geometry/construction/line_connect.h"
#include "geometry/construction/triangle_make.h"

namespace Core {

/// Registers all the constructions available currently.
void RegisterAllConstructions(System& system) {
    system.RegisterConstruction<LineConnect>();
    system.RegisterConstruction<TriangleMake>();
}

} // namespace Core

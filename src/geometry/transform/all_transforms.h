// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/system.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/parallel/angles_to_parallel.h"
#include "geometry/transform/parallel/line_parallel_transitivity.h"
#include "geometry/transform/parallel/parallel_to_angles.h"
#include "geometry/transform/parallel/prependicular_to_angles.h"
#include "geometry/transform/pythagorean/pythagorean.h"

namespace Core {

/// Registers all the transforms available currently.
void RegisterAllTransforms(System& system) {
    system.RegisterTransform<LineParallelTransitivity>();
    system.RegisterTransform<LineSegmentConcat>();
    system.RegisterTransform<Pythagorean>();
    system.RegisterTransform<ParallelToAngles>();
    system.RegisterTransform<AnglesToParallel>();
    system.RegisterTransform<PrependicularToAngles>();
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/system.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/all_transforms.h"
#include "geometry/transform/parallel/angles_to_parallel.h"
#include "geometry/transform/parallel/angles_to_prependicular.h"
#include "geometry/transform/parallel/line_parallel_transitivity.h"
#include "geometry/transform/parallel/parallel_to_angles.h"
#include "geometry/transform/parallel/prependicular_to_angles.h"
#include "geometry/transform/pythagorean/pythagorean.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

void RegisterAllTransforms(System& system) {
    // Algebra
    system.RegisterTransform<LineSegmentConcat>();

    // Parallel
    system.RegisterTransform<LineParallelTransitivity>();
    system.RegisterTransform<ParallelToAngles>();
    system.RegisterTransform<AnglesToParallel>();
    system.RegisterTransform<PrependicularToAngles>();
    system.RegisterTransform<AnglesToPrependicular>();

    // Pythagorean
    system.RegisterTransform<Pythagorean>();

    // Triangle
    system.RegisterTransform<TriangleInternalAngles>();
}

} // namespace Core

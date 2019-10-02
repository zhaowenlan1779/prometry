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
#include "geometry/transform/triangle/aa_similar.h"
#include "geometry/transform/triangle/angles_to_isosceles.h"
#include "geometry/transform/triangle/hl_similar.h"
#include "geometry/transform/triangle/isosceles_to_angles.h"
#include "geometry/transform/triangle/sas_similar.h"
#include "geometry/transform/triangle/similar_to_angles.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"
#include "geometry/transform/triangle/sss_similar.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

void RegisterAllTransforms(System& system) {
    // Algebra
    system.RegisterTransform<LineSegmentConcat>();

    // Parallel
    system.RegisterTransform<AnglesToParallel>();
    system.RegisterTransform<AnglesToPrependicular>();
    system.RegisterTransform<LineParallelTransitivity>();
    system.RegisterTransform<ParallelToAngles>();
    system.RegisterTransform<PrependicularToAngles>();

    // Pythagorean
    system.RegisterTransform<Pythagorean>();

    // Triangle
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<AnglesToIsosceles>();
    system.RegisterTransform<HLSimilar>();
    system.RegisterTransform<IsoscelesToAngles>();
    system.RegisterTransform<SAS_Similar>();
    system.RegisterTransform<SimilarToAngles>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    system.RegisterTransform<SSS_Similar>();
    system.RegisterTransform<TriangleInternalAngles>();
}

} // namespace Core

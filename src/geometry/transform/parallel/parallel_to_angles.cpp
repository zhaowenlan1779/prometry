// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/parallel_to_angles.h"

namespace Core {

ParallelToAngles::ParallelToAngles() = default;

ParallelToAngles::~ParallelToAngles() = default;

void ParallelToAngles::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::LineParallel)) {
        const auto& elements = conclusion->GetRelatedElements();

        for (const auto& line : system.GetElements(Elements::Line)) {
            if (line == elements[0] || line == elements[1])
                continue;

            const auto& l = std::dynamic_pointer_cast<Line>(line);
            const auto& l1 = std::dynamic_pointer_cast<Line>(elements[0]);
            const auto& l2 = std::dynamic_pointer_cast<Line>(elements[1]);
            if (system.GetConclusion(LineParallel(l, l1)) ||
                system.GetConclusion(LineParallel(l, l2))) {
                continue;
            }

            if (Intersection<Point>(l, l1).empty() || Intersection<Point>(l, l2).empty()) {
                continue;
            }

            system.Algebra().AddEquation(
                LineAngle(l, LineDirection::Normal, l1, LineDirection::Normal) -
                    LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal),
                "parallel to angles", {conclusion->GetProofNode()});
        }
    }
}

} // namespace Core

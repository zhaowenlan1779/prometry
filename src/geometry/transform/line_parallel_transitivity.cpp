// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

LineParallelTransitivity::LineParallelTransitivity() = default;

LineParallelTransitivity::~LineParallelTransitivity() = default;

void LineParallelTransitivity::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::LineParallel)) {
        const auto& elements = conclusion->GetRelatedElements();

        for (const auto i : {0, 1}) {
            for (const auto& conclusion2 : elements[i]->GetConclusions(Conclusions::LineParallel)) {
                if (conclusion2 == conclusion) {
                    continue;
                }

                const auto& elements2 = conclusion2->GetRelatedElements();
                const auto& other_element =
                    (elements2[0] == elements[i] ? elements2[1] : elements2[0]);
                system.CreateConclusion<LineParallel>(
                    "transitivity of line parallel", {conclusion, conclusion2},
                    std::dynamic_pointer_cast<Line>(elements[1 - i]),
                    std::dynamic_pointer_cast<Line>(other_element));
            }
        }
    }
}

} // namespace Core

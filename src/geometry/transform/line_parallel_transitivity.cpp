// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

LineParallelTransitivity::~LineParallelTransitivity() = default;

void LineParallelTransitivity::Execute(System& system) {

    for (const auto& conclusion : system.GetConclusions(Conclusions::LineParallel)) {
        const auto& elements = conclusion->GetRelatedElements();

#define CHECK(i)                                                                                   \
    for (const auto& conclusion2 : elements[1 - i]->GetConclusions(Conclusions::LineParallel)) {   \
        const auto& elements2 = conclusion2->GetRelatedElements();                                 \
        const auto& other_element =                                                                \
            (elements2[0] == elements[1 - i] ? elements2[1] : elements2[0]);                       \
        if (other_element != elements[i]) {                                                        \
            system.CreateConclusion<LineParallel>("transitivity of line parallel",                 \
                                                  {conclusion, conclusion2},                       \
                                                  std::dynamic_pointer_cast<Line>(elements[0]),    \
                                                  std::dynamic_pointer_cast<Line>(other_element)); \
        }                                                                                          \
    }

        CHECK(0);
        CHECK(1);
#undef CHECK
    }
}

} // namespace Core

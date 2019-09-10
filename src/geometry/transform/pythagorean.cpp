// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/conclusion/conclusion_types.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line_segment.h"
#include "geometry/transform/pythagorean.h"

namespace Core {

Pythagorean::~Pythagorean() = default;

void Pythagorean::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::LinePrependicular)) {
        const auto& elements = conclusion->GetRelatedElements();
        const auto& point = Intersection<Point>(elements[0], elements[1]);
        ASSERT_MSG(point.size() == 1, "Prependicular lines must have a intersection point");

        for (const auto& p1_weak : elements[0]->children[Elements::Point]) {
            for (const auto& p2_weak : elements[1]->children[Elements::Point]) {
                if (auto p1 = p1_weak.lock()) {
                    if (auto p2 = p2_weak.lock()) {
                        if (p1 == p2 || p1 == point[0] || p2 == point[0]) {
                            continue;
                        }
                        const auto a =
                            LineSegmentLength(point[0], std::dynamic_pointer_cast<Point>(p1));
                        const auto b =
                            LineSegmentLength(point[0], std::dynamic_pointer_cast<Point>(p2));
                        const auto c = LineSegmentLength(std::dynamic_pointer_cast<Point>(p1),
                                                         std::dynamic_pointer_cast<Point>(p2));
                        system.Algebra().AddEquation(a * a + b * b - c * c);
                    }
                }
                // TODO: else?
            }
        }
    }
}

} // namespace Core

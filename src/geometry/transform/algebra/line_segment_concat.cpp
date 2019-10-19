// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/system.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/transform/algebra/line_segment_concat.h"

namespace Core {

LineSegmentConcat::LineSegmentConcat() = default;

LineSegmentConcat::~LineSegmentConcat() = default;

/*static*/ void LineSegmentConcat::Execute(System& system, const std::shared_ptr<Line>& line) {
    const auto& points = line->children[Elements::Point];
    for (std::size_t i = 0; i < points.size(); ++i) {
        for (std::size_t j = i + 1; j < points.size(); ++j) {
            for (std::size_t k = j + 1; k < points.size(); ++k) {
                const auto& p1 = std::dynamic_pointer_cast<Point>(points[i].lock());
                const auto& p2 = std::dynamic_pointer_cast<Point>(points[j].lock());
                const auto& p3 = std::dynamic_pointer_cast<Point>(points[k].lock());
                system.Algebra().AddEquation(LineSegmentLength(p1, p2) + LineSegmentLength(p2, p3) -
                                                 LineSegmentLength(p1, p3),
                                             "line segment concat");
            }
        }
    }
}

} // namespace Core

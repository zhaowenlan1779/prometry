// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"

namespace Core {

SimilarToLineSegmentRatio::SimilarToLineSegmentRatio() = default;

SimilarToLineSegmentRatio::~SimilarToLineSegmentRatio() = default;

void SimilarToLineSegmentRatio::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::TriangleSimilar)) {
        const auto& similar = std::dynamic_pointer_cast<TriangleSimilar>(conclusion);
        const auto& elements = similar->GetRelatedElements();

        std::array<std::shared_ptr<Triangle>, 2> triangles{
            {std::dynamic_pointer_cast<Triangle>(elements[0]),
             std::dynamic_pointer_cast<Triangle>(elements[1])}};

        std::array<Algebra::Expression, 3> line_segments{
            {triangles[0]->length_a, triangles[0]->length_b, triangles[0]->length_c}};
        ApplyTransform(similar->GetOrder(), line_segments);

        const auto& ratio = similar->GetSimilarRatio();

        system.Algebra().AddEquation(triangles[1]->length_a - ratio * line_segments[0],
                                     "similar to line segment ratio", {similar->GetProofNode()});
        system.Algebra().AddEquation(triangles[1]->length_b - ratio * line_segments[1],
                                     "similar to line segment ratio", {similar->GetProofNode()});
        system.Algebra().AddEquation(triangles[1]->length_c - ratio * line_segments[2],
                                     "similar to line segment ratio", {similar->GetProofNode()});
    }
}

} // namespace Core

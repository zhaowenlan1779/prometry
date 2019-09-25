// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/similar_to_angles.h"

namespace Core {

SimilarToAngles::SimilarToAngles() = default;

SimilarToAngles::~SimilarToAngles() = default;

void SimilarToAngles::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::TriangleSimilar)) {
        const auto& similar = std::dynamic_pointer_cast<TriangleSimilar>(conclusion);
        const auto& elements = similar->GetRelatedElements();

        std::array<std::shared_ptr<Triangle>, 2> triangles{
            {std::dynamic_pointer_cast<Triangle>(elements[0]),
             std::dynamic_pointer_cast<Triangle>(elements[1])}};

        std::array<Algebra::Expression, 3> angles{
            {triangles[1]->angle_A, triangles[1]->angle_B, triangles[1]->angle_C}};
        ApplyTransform(similar->GetOrder(), angles);

        system.Algebra().AddEquation(triangles[0]->angle_A - angles[0]);
        system.Algebra().AddEquation(triangles[0]->angle_B - angles[1]);
        system.Algebra().AddEquation(triangles[0]->angle_C - angles[2]);
    }
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/sas_similar.h"

namespace Core {

SAS_Similar::SAS_Similar() = default;

SAS_Similar::~SAS_Similar() = default;

/*static*/ void SAS_Similar::Execute(System& system, const std::shared_ptr<Triangle>& t1,
                                     const std::shared_ptr<Triangle>& t2) {

    for (int i = 0; i < TriangleOrders::Count; ++i) {
        std::array<Algebra::Expression, 3> edges{{t1->length_a, t1->length_b, t1->length_c}};
        ApplyTransform(TriangleOrder(i), edges);
        std::array<Algebra::Expression, 3> angles{{t1->angle_A, t1->angle_B, t1->angle_C}};
        ApplyTransform(TriangleOrder(i), angles);

        const auto CheckSimilar = [&](const Algebra::Expression& t1_angle,
                                      const Algebra::Expression& t2_angle,
                                      const Algebra::Expression& t1_edge1,
                                      const Algebra::Expression& t2_edge1,
                                      const Algebra::Expression& t1_edge2,
                                      const Algebra::Expression& t2_edge2) {
            const auto& [ret1, proof_node1] = system.Algebra().CheckEquation(t1_angle - t2_angle);
            if (!ret1) {
                return;
            }

            const auto& [ret2, proof_node2] =
                system.Algebra().CheckEquation(t2_edge1 / t1_edge1 - t2_edge2 / t1_edge2);
            if (ret2) {
                system.CreateConclusion<TriangleSimilar>("SAS similar", {proof_node1, proof_node2},
                                                         t1, t2, TriangleOrder(i));
            }
        };

        CheckSimilar(angles[0], t2->angle_A, edges[1], t2->length_b, edges[2], t2->length_c);
        CheckSimilar(angles[1], t2->angle_B, edges[0], t2->length_a, edges[2], t2->length_c);
        CheckSimilar(angles[2], t2->angle_C, edges[0], t2->length_a, edges[1], t2->length_b);
    }
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/aa_similar.h"

namespace Core {

AASimilar::AASimilar() = default;

AASimilar::~AASimilar() = default;

/*static*/ void AASimilar::Execute(System& system, const std::shared_ptr<Triangle>& t1,
                                   const std::shared_ptr<Triangle>& t2) {

    for (int i = 0; i < TriangleOrders::Count; ++i) {
        std::array<Algebra::Expression, 3> angles{{t1->angle_A, t1->angle_B, t1->angle_C}};
        ApplyTransform(TriangleOrder(i), angles);
        const auto& [ret1, proof_node1] = system.Algebra().CheckEquation(angles[0] - t2->angle_A);
        if (!ret1)
            continue;
        const auto& [ret2, proof_node2] = system.Algebra().CheckEquation(angles[1] - t2->angle_B);
        if (!ret2)
            continue;
        system.CreateConclusion<TriangleSimilar>("AA similar", {proof_node1, proof_node2}, t1, t2,
                                                 TriangleOrder(i));
    }
}

} // namespace Core

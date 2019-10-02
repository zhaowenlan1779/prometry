// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/transform/triangle/isosceles_to_angles.h"

namespace Core {

IsoscelesToAngles::IsoscelesToAngles() = default;

IsoscelesToAngles::~IsoscelesToAngles() = default;

/*static*/ void IsoscelesToAngles::Execute(System& system, const std::shared_ptr<Triangle>& t) {
    const auto CheckIsosceles = [&system, &t](const Algebra::Expression& angle_1,
                                              const Algebra::Expression& angle_2,
                                              const Algebra::Expression& edge_1,
                                              const Algebra::Expression& edge_2) {
        const auto& [ret, proof_node] = system.Algebra().CheckEquation(edge_1 - edge_2);
        if (ret) {
            system.Algebra().AddEquation(angle_1 - angle_2, "isosceles to angles", {proof_node});
        }
    };

    CheckIsosceles(t->angle_A, t->angle_B, t->length_a, t->length_b);
    CheckIsosceles(t->angle_A, t->angle_C, t->length_a, t->length_c);
    CheckIsosceles(t->angle_B, t->angle_C, t->length_b, t->length_c);
}

} // namespace Core

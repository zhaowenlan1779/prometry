// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/transform/triangle/angles_to_isosceles.h"

namespace Core {

AnglesToIsosceles::AnglesToIsosceles() = default;

AnglesToIsosceles::~AnglesToIsosceles() = default;

/*static*/ void AnglesToIsosceles::Execute(System& system, const std::shared_ptr<Triangle>& t) {
    const auto CheckIsosceles = [&system, &t](const Algebra::Expression& angle_1,
                                              const Algebra::Expression& angle_2,
                                              const Algebra::Expression& edge_1,
                                              const Algebra::Expression& edge_2) {
        const auto& [ret, proof_node] = system.Algebra().CheckEquation(angle_1 - angle_2);
        if (ret) {
            system.Algebra().AddEquation(edge_1 - edge_2, "angles to isosceles", {proof_node});
        }
    };

    CheckIsosceles(t->angle_A, t->angle_B, t->length_a, t->length_b);
    CheckIsosceles(t->angle_A, t->angle_C, t->length_a, t->length_c);
    CheckIsosceles(t->angle_B, t->angle_C, t->length_b, t->length_c);
}

} // namespace Core

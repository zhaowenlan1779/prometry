// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/transform/pythagorean/pythagorean.h"

namespace Core {

Pythagorean::Pythagorean() = default;

Pythagorean::~Pythagorean() = default;

/*static*/ void Pythagorean::Execute(System& system, const std::shared_ptr<Triangle>& t) {
#define CHECK(angle, long, short1, short2)                                                         \
    if (system.Algebra().CheckEquation(t->angle - SymEngine::Expression(SymEngine::pi) / 2)) {     \
        system.Algebra().AddEquation(t->short1 * t->short1 + t->short2 * t->short2 -               \
                                     t->long * t->long);                                           \
    }

    CHECK(angle_A, length_a, length_b, length_c);
    CHECK(angle_B, length_b, length_a, length_c);
    CHECK(angle_C, length_c, length_a, length_b);
#undef CHECK
}

} // namespace Core

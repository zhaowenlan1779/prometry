// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TriangleInternalAngles::TriangleInternalAngles() = default;

TriangleInternalAngles::~TriangleInternalAngles() = default;

/*static*/ void TriangleInternalAngles::Execute(System& system,
                                                const std::shared_ptr<Triangle>& t) {
    system.Algebra().AddEquation(t->angle_A + t->angle_B + t->angle_C - SymEngine::pi,
                                 "triangle internal angles", {});
}

} // namespace Core

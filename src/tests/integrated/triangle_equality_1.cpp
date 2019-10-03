// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/triangle/aa_similar.h"
#include "geometry/transform/triangle/isosceles_to_angles.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("TriangleEquality_1", "[integrated]") {
    System system;
    system.RegisterTransform<AASimilar>();
    system.RegisterTransform<IsoscelesToAngles>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    system.RegisterTransform<TriangleInternalAngles>();
    system.RegisterConstruction<TriangleMake>();

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto l = system.CreateElement<Line>("", "l");

    d->AddParent(l);
    b->AddParent(l);
    c->AddParent(l);
    e->AddParent(l);

    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, c));
    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(a, e));

    const auto proof = system.Execute([&b, &c, &d, &e](System& system) {
        const auto& [ret, proof_node] =
            system.Algebra().CheckEquation(LineSegmentLength(b, d) - LineSegmentLength(c, e));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core

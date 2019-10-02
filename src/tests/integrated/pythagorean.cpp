// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/construction/all_constructions.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/parallel/prependicular_to_angles.h"
#include "geometry/transform/pythagorean/pythagorean.h"

namespace Core {

TEST_CASE("Pythagorean+LineSegmentConcat", "[integrated]") {
    System system;
    system.RegisterTransform<LineSegmentConcat>();
    system.RegisterTransform<PrependicularToAngles>();
    system.RegisterTransform<Pythagorean>();
    system.RegisterConstruction<TriangleMake>();

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    system.CreateConclusion<LinePrependicular>("", {}, l1, l2);

    a->AddParent(l1);
    b->AddParent(l2);
    c->AddParent(l1);
    c->AddParent(l2);
    d->AddParent(l2);

    system.Algebra().AddEquation(LineSegmentLength(a, c) - 1);
    system.Algebra().AddEquation(LineSegmentLength(b, c) - 3);
    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(d, b));

    const auto proof = system.Execute([&a, &d](System& system) {
        const auto& [ret, proof_node] = system.Algebra().CheckEquation(
            LineSegmentLength(a, d) - Algebra::Expression(5) / Algebra::Expression(3));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core

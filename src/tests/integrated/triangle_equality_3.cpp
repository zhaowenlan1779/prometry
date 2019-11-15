// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/all_constructions.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/all_transforms.h"

namespace Core {

TEST_CASE("TriangleEquality_3", "[integrated]") {
    System system;
    RegisterAllTransforms(system);
    RegisterAllConstructions(system);

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");
    auto ab = system.CreateElement<Line>("", "AB");
    auto ac = system.CreateElement<Line>("", "AC");
    auto be = system.CreateElement<Line>("", "BE");
    auto dc = system.CreateElement<Line>("", "DC");

    a->AddParent(ab);
    d->AddParent(ab);
    b->AddParent(ab);

    a->AddParent(ac);
    e->AddParent(ac);
    c->AddParent(ac);

    b->AddParent(be);
    f->AddParent(be);
    e->AddParent(be);

    d->AddParent(dc);
    f->AddParent(dc);
    c->AddParent(dc);

    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(a, e), "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, c), "hypothesis");

    const auto proof = system.Execute([&b, &c, &f, &e, &d](System& system) {
        const auto& [ret, proof_node] =
            system.Algebra().CheckEquation(LineSegmentLength(b, f) - LineSegmentLength(f, c));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core

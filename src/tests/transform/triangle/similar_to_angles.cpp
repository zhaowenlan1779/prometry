// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/similar_to_angles.h"

namespace Core {

TEST_CASE("SimilarToAngles", "[transform]") {
    System system;
    system.RegisterTransform<SimilarToAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, f, d, e);

    // Let ABC similar FDE
    system.CreateConclusion<TriangleSimilar>("", {}, t1, order1, t2, order2);

    system.Execute([](System& system) { return nullptr; });

    {
        const auto& [ba, dir1] = Line::Connect(system, b, a);
        const auto& [bc, dir2] = Line::Connect(system, b, c);
        const auto& [df, dir3] = Line::Connect(system, d, f);
        const auto& [de, dir4] = Line::Connect(system, d, e);
        REQUIRE(system.Algebra()
                    .CheckEquation(LineAngle(ba, dir1, bc, dir2) - LineAngle(df, dir3, de, dir4))
                    .first);
    }

    {
        const auto& [cb, dir1] = Line::Connect(system, c, b);
        const auto& [ca, dir2] = Line::Connect(system, c, a);
        const auto& [ed, dir3] = Line::Connect(system, e, d);
        const auto& [ef, dir4] = Line::Connect(system, e, f);
        REQUIRE(system.Algebra()
                    .CheckEquation(LineAngle(cb, dir1, ca, dir2) - LineAngle(ed, dir3, ef, dir4))
                    .first);
    }

    {
        const auto& [ac, dir1] = Line::Connect(system, a, c);
        const auto& [ab, dir2] = Line::Connect(system, a, b);
        const auto& [fe, dir3] = Line::Connect(system, f, e);
        const auto& [fd, dir4] = Line::Connect(system, f, d);
        REQUIRE(system.Algebra()
                    .CheckEquation(LineAngle(ac, dir1, ab, dir2) - LineAngle(fe, dir3, fd, dir4))
                    .first);
    }
}

// TODO: More, better tests...

} // namespace Core

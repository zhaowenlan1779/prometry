// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"
#include "geometry/element/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/line_parallel_transitivity.h"
#include "geometry/transform/parallel_to_angles.h"

namespace Core {

TEST_CASE("ParallelToAngles", "[transform]") {
    System system;
    system.RegisterTransform<LineParallelTransitivity>();
    system.RegisterTransform<ParallelToAngles>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto l = system.CreateElement<Line>("", "l");
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");
    system.CreateConclusion<LineParallel>("", {}, l1, l2);
    system.CreateConclusion<LineParallel>("", {}, l2, l3);

    p1->AddParent(l1);
    p1->AddParent(l);
    p2->AddParent(l2);
    p2->AddParent(l);
    p3->AddParent(l3);
    p3->AddParent(l);

    system.Execute([](System&) { return nullptr; });

    for (auto dir1 : {LineDirection::Normal, LineDirection::Reversed}) {
        for (auto dir2 : {LineDirection::Normal, LineDirection::Reversed}) {
            REQUIRE(system.Algebra().CheckEquation(LineAngle(l1, dir1, l, dir2) -
                                                   LineAngle(l2, dir1, l, dir2)));
            REQUIRE(system.Algebra().CheckEquation(LineAngle(l1, dir1, l, dir2) -
                                                   LineAngle(l3, dir1, l, dir2)));
        }
    }
}

} // namespace Core

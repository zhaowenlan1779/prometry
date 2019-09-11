// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"
#include "geometry/transform/line_parallel_transitivity.h"

namespace Core {

TEST_CASE("LineParallelTransitivity", "[transform]") {
    System system;
    system.RegisterTransform<LineParallelTransitivity>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto l4 = system.CreateElement<Line>("", "l4");
    system.CreateConclusion<LineParallel>("", {}, l1, l2);
    system.CreateConclusion<LineParallel>("", {}, l2, l3);
    system.CreateConclusion<LineParallel>("", {}, l3, l4);

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetConclusion(LineParallel(l1, l3)) != nullptr);
    REQUIRE(system.GetConclusion(LineParallel(l1, l4)) != nullptr);
    REQUIRE(system.GetConclusion(LineParallel(l2, l4)) != nullptr);
}

} // namespace Core

// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"
#include "geometry/transform/all_transforms.h"

#include <iostream>

namespace Core {

TEST_CASE("ProofOutput[LineParallelTransitivity]", "[integrated]") {
    System system;
    RegisterAllTransforms(system);
    StandaloneLine* l1 = new StandaloneLine("l1");
    StandaloneLine* l2 = new StandaloneLine("l2");
    StandaloneLine* l3 = new StandaloneLine("l3");
    StandaloneLine* l4 = new StandaloneLine("l4");
    system.AddElement(l1);
    system.AddElement(l2);
    system.AddElement(l3);
    system.AddElement(l4);
    system.AddConclusion(new LineParallel(*l1, *l2));
    system.AddConclusion(new LineParallel(*l2, *l3));
    system.AddConclusion(new LineParallel(*l3, *l4));

    auto proof = system.Execute(
        [&l1, &l4](System& system) { return system.GetConclusion(LineParallel(*l1, *l4)); });

    std::cout << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core
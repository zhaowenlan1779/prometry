// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line.h"
#include "geometry/transform/parallel/line_parallel_transitivity.h"

#include <iostream>

namespace Core {

TEST_CASE("ProofOutput[LineParallelTransitivity]", "[integrated]") {
    System system;
    system.RegisterTransform<LineParallelTransitivity>();

    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto l4 = system.CreateElement<Line>("", "l4");
    system.CreateConclusion<LineParallel>("", {}, l1, l2);
    system.CreateConclusion<LineParallel>("", {}, l2, l3);
    system.CreateConclusion<LineParallel>("", {}, l3, l4);

    const auto proof = system.Execute([&l1, &l4](System& system) {
        auto conclusion = system.GetConclusion(LineParallel(l1, l4));
        return conclusion ? conclusion->GetProofNode() : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core
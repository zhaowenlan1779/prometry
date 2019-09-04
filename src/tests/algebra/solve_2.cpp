// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <algorithm>
#include <catch2/catch.hpp>
#include <symengine/visitor.h>
#include "algebra/algebra.h"

namespace Algebra {

TEST_CASE("Solve2", "[algebra]") {
    System system;

    Expression x("x");
    Expression y("y");

    // x + y = 7,
    // x*x + y*y = 25
    system.AddEquation(x + y - 7);
    system.AddEquation(x * x + y * y - 25);

#define REQUIRE_CONTAINS(a, b) REQUIRE(std::find(a.begin(), a.end(), expand((b))) != a.end())

    using SymEngine::integer;
    using SymEngine::symbol;

    { // Testset 1: x ()
        auto solns = system.TrySolveAll(symbol("x"), {});

        REQUIRE(solns.size() == 2);
        REQUIRE_CONTAINS(solns, integer(3));
        REQUIRE_CONTAINS(solns, integer(4));
    }

    { // Testset 2: y ()
        auto solns = system.TrySolveAll(symbol("y"), {});

        REQUIRE(solns.size() == 2);
        REQUIRE_CONTAINS(solns, integer(3));
        REQUIRE_CONTAINS(solns, integer(4));
    }

#undef REQUIRE_CONTAINS
}
} // namespace Algebra

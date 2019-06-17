// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <algorithm>
#include <catch2/catch.hpp>
#include <symengine/visitor.h>
#include "algebra/algebra.h"

namespace Algebra {

TEST_CASE("Solve1", "[algebra]") {
    System system;

    Expression x("x");
    Expression y("y");
    Expression z("z");

    // 3x+y = 2,
    // y+z  = 1
    system.AddEquation(3 * x + y - 2);
    system.AddEquation(y + z - 1);

#define REQUIRE_CONTAINS(a, b) REQUIRE(std::find(a.begin(), a.end(), expand((b))) != a.end())

    using SymEngine::free_symbols;
    using SymEngine::rcp_static_cast;
    using SymEngine::symbol;

    { // Testset 1: x (y)
        auto solns = system.TrySolveAll(symbol("x"), {symbol("y")});

        REQUIRE(solns.size() == 1);
        REQUIRE_CONTAINS(solns, (2 - y) / 3);
    }

    { // Testset 2: x (z)
        auto solns = system.TrySolveAll(symbol("x"), {symbol("z")});

        REQUIRE(solns.size() == 1);
        REQUIRE_CONTAINS(solns, (1 + z) / 3);
    }

    { // Testset 3: x (y, z)
        auto solns = system.TrySolveAll(symbol("x"), {symbol("y"), symbol("z")});

        for (const auto& soln : solns) {
            for (const auto& symbol : free_symbols(soln)) {
                Algebra::Symbol symbol_ptr = rcp_static_cast<const SymEngine::Symbol>(symbol);
                REQUIRE((symbol_ptr->get_name() == "y" || symbol_ptr->get_name() == "z"));
            }
        }
    }

    { // Testset 4: x () (Unsolveable)
        auto solns = system.TrySolveAll(symbol("x"), {});

        REQUIRE(solns.empty());
    }

#undef REQUIRE_CONTAINS
}
} // namespace Algebra

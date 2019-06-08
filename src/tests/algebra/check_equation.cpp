// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "algebra/algebra.h"

namespace Algebra {

TEST_CASE("CheckEquation", "[algebra]") {
    System system;

    using namespace SymEngine;
    Expression x("x");
    Expression y("y");
    Expression z("z");

    // 3x+y = 2,
    // y+z  = 1
    system.AddEquation(3 * x + y - 2);
    system.AddEquation(y + z - 1);

    REQUIRE(system.CheckEquation(3 * x + y - 2));
    REQUIRE(system.CheckEquation(y + z - 1));
    REQUIRE(system.CheckEquation(3 * x + 2 * y + z - 3));
    REQUIRE(system.CheckEquation(3 * x - z - 1));
    REQUIRE(system.CheckEquation(6 * x - 2 * z - 2));
    REQUIRE(system.CheckEquation(12 * x + 4 * y - 8));
    REQUIRE(system.CheckEquation(3 * x - y - 2 * z));
    REQUIRE_FALSE(system.CheckEquation(x + y));
    REQUIRE_FALSE(system.CheckEquation(3 * x + y));
    REQUIRE_FALSE(system.CheckEquation(z));
}

} // namespace Algebra

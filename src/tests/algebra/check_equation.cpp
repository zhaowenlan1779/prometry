// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "algebra/algebra.h"

namespace Algebra {

TEST_CASE("CheckEquation", "[algebra]") {
    System system;

    Expression x("x");
    Expression y("y");
    Expression z("z");

    // 3x+y = 2,
    // y+z  = 1
    system.AddEquation(3 * x + y - 2);
    system.AddEquation(y + z - 1);

    REQUIRE(system.CheckEquation(3 * x + y - 2).first);
    REQUIRE(system.CheckEquation(y + z - 1).first);
    REQUIRE(system.CheckEquation(3 * x + 2 * y + z - 3).first);
    REQUIRE(system.CheckEquation(3 * x - z - 1).first);
    REQUIRE(system.CheckEquation(6 * x - 2 * z - 2).first);
    REQUIRE(system.CheckEquation(12 * x + 4 * y - 8).first);
    REQUIRE(system.CheckEquation(3 * x - y - 2 * z).first);
    REQUIRE_FALSE(system.CheckEquation(x + y).first);
    REQUIRE_FALSE(system.CheckEquation(3 * x + y).first);
    REQUIRE_FALSE(system.CheckEquation(z).first);
}

} // namespace Algebra

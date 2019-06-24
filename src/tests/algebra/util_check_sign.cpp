// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include <symengine/expression.h>
#include "algebra/util.h"

namespace Algebra {

TEST_CASE("CheckSign", "[algebra]") {
    SymEngine::Expression x("x");
    SymEngine::Expression y("y");
    SymEngine::Expression z("z");

    REQUIRE(CheckSign(3 * x + 2 * y) == 1);
    REQUIRE(CheckSign(2 * x - y) == 0);
    REQUIRE(CheckSign(5 * x + 2 * y + z) == 1);
    REQUIRE(CheckSign(-x - y) == -1);
    REQUIRE(CheckSign(SymEngine::number(-12)) == -1);
    REQUIRE(CheckSign(3 * x - 8) == 0);
    REQUIRE(CheckSign(3 * x + 8) == 1);
    REQUIRE(CheckSign(-3 * x - 8) == -1);
    REQUIRE(CheckSign(x * x + 2 * y + z) == 1);
    REQUIRE(CheckSign(-x * x * x) == -1);
    REQUIRE(CheckSign(x * x * x - y * y * 2) == 0);
    REQUIRE(CheckSign(SymEngine::sqrt(x * x + y)) == 1);
    REQUIRE(CheckSign(-SymEngine::Expression(SymEngine::sqrt(x * x + y))) == -1);
    REQUIRE(CheckSign(SymEngine::Expression(SymEngine::sqrt(x * x + y)) -
                      SymEngine::Expression(SymEngine::sqrt(x * x - y))) == 0);
}

} // namespace Algebra

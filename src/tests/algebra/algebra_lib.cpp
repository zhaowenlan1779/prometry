// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "algebra/algebra.h"

namespace Algebra {

TEST_CASE("AlgebraLib", "[algebra]") {
    Expression x("x");
    Expression y("y");
    Expression z("z");

    REQUIRE((x * x / x) == x);
    REQUIRE(((x * y * 2) / (2 * z)) == (x * y) / z);
}

} // namespace Algebra

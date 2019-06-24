// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include <symengine/expression.h>
#include "algebra/util.h"

namespace Algebra {

TEST_CASE("SimplifyEquation", "[algebra]") {
    SymEngine::Expression x("x");
    SymEngine::Expression y("y");
    SymEngine::Expression z("z");

    using SymEngine::sqrt;
    using SymEngine::sub;

#define REQUIRE_SAME(equ1, equ2) REQUIRE(((equ1) == expand((equ2)) || (equ1) == expand(-(equ2))))
    REQUIRE_SAME(SimplifyEquation(sqrt(x * x - 2) - y), x * x - y * y - 2);
    REQUIRE_SAME(SimplifyEquation(sqrt(x * x - 2) - y - z), (y + z) * (y + z) - x * x + 2);
#undef REQUIRE_SAME
}

} // namespace Algebra

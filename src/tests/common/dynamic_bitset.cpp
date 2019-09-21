// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "common/dynamic_bitset.h"

TEST_CASE("DynamicBitset", "[common]") {
    Common::DynamicBitset bs_1;

    SECTION("setting individual bits") {
        // OR-ing
        bs_1 |= 3;
        bs_1 |= 7;

        // Check size
        REQUIRE(bs_1.Size() >= 8);

        // Check bits
        REQUIRE(bs_1.At(3));
        REQUIRE(bs_1.At(7));
        REQUIRE_FALSE(bs_1.At(0));
        REQUIRE_FALSE(bs_1.At(1));
        REQUIRE_FALSE(bs_1.At(120));

        // Simple AND-ing
        bs_1 &= 3;

        REQUIRE(bs_1.At(3));
        REQUIRE_FALSE(bs_1.At(7));

        // More AND-ing
        bs_1 &= 12;

        REQUIRE_FALSE(bs_1.At(3));
    }

    SECTION("operating multiple sets") {
        bs_1 |= 10;
        bs_1 |= 5;

        Common::DynamicBitset bs_2;
        bs_2 |= 7;
        bs_2 |= 8;
        bs_2 |= 10;

        {
            const auto& or_set = bs_1 | bs_2;
            REQUIRE(or_set.Size() >= 11);
            REQUIRE(or_set.At(10));
            REQUIRE(or_set.At(5));
            REQUIRE(or_set.At(7));
            REQUIRE(or_set.At(8));
        }

        {
            const auto& and_set = bs_1 & bs_2;
            REQUIRE(and_set.At(10));
            REQUIRE_FALSE(and_set.At(5));
            REQUIRE_FALSE(and_set.At(7));
            REQUIRE_FALSE(and_set.At(8));
        }
    }
}

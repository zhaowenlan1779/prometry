// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <catch2/catch.hpp>
#include "common/printer.h"

TEST_CASE("StringPack", "[common]") {
    using Common::PrintFormat;

    SECTION("constructing string packs with strings") {
        Common::StringPack sp = "Hello, world!";

        REQUIRE(sp.Get(PrintFormat::Plain) == "Hello, world!");
        REQUIRE(sp.Get(PrintFormat::Latex) == "Hello, world!");

        SECTION("concating string packs with strings") {
            sp += "Goodbye!";
            REQUIRE(sp.Get(PrintFormat::Plain) == "Hello, world!Goodbye!");
            REQUIRE(sp.Get(PrintFormat::Latex) == "Hello, world!Goodbye!");
        }

        SECTION("concating string packs with string arrays") {
            sp += {"Plain", "Latex"};
            REQUIRE(sp.Get(PrintFormat::Plain) == "Hello, world!Plain");
            REQUIRE(sp.Get(PrintFormat::Latex) == "Hello, world!Latex");
        }
    }

    SECTION("constructing string packs with string array") {
        Common::StringPack sp = {"Hello, earth!", "Hello, moon!"};

        REQUIRE(sp.Get(PrintFormat(PrintFormat::Plain)) == "Hello, earth!");
        REQUIRE(sp.Get(PrintFormat(PrintFormat::Latex)) == "Hello, moon!");

        SECTION("combining string packs with strings") {
            sp += "Goodbye!";
            REQUIRE(sp.Get(PrintFormat::Plain) == "Hello, earth!Goodbye!");
            REQUIRE(sp.Get(PrintFormat::Latex) == "Hello, moon!Goodbye!");
        }

        SECTION("combining string packs with string arrays") {
            sp += {"Plain", "Latex"};
            REQUIRE(sp.Get(PrintFormat::Plain) == "Hello, earth!Plain");
            REQUIRE(sp.Get(PrintFormat::Latex) == "Hello, moon!Latex");
        }
    }
}

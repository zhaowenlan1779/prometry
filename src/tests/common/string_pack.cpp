// Copyright 2019 Zhupengfei and others
// Licensed under the MIT License.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

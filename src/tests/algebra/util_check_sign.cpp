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
    REQUIRE(CheckSign((x * y) / (y + z)) == 1);
    REQUIRE(CheckSign(x + y / z) == 1);
    REQUIRE(CheckSign(x - y / z) == 0);
    REQUIRE(CheckSign((-x * y) / (z + x)) == -1);
    REQUIRE(CheckSign(-x - y / z) == -1);
    REQUIRE(CheckSign(SymEngine::sqrt(x * x + y) - y / z) == 0);
    REQUIRE(CheckSign(SymEngine::sqrt(x * x + y) + y / z) == 1);
    REQUIRE(CheckSign(SymEngine::sqrt(x - 1)) == 1);
    REQUIRE(CheckSign(SymEngine::sqrt(x - 3) - x) == 0);
    REQUIRE(CheckSign(-SymEngine::Expression(SymEngine::sqrt(x - 2)) - x - 3) == -1);
}

} // namespace Algebra

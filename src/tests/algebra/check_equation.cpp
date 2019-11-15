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

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

TEST_CASE("AlgebraLib", "[algebra]") {
    Expression x("x");
    Expression y("y");
    Expression z("z");

    REQUIRE((x * x / x) == x);
    REQUIRE(((x * y * 2) / (2 * z)) == (x * y) / z);
    REQUIRE(SymEngine::pow(x, -1) == 1 / x);
}

} // namespace Algebra

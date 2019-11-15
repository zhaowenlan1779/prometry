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

TEST_CASE("SimplifyEquation", "[algebra]") {
    SymEngine::Expression x("x");
    SymEngine::Expression y("y");
    SymEngine::Expression z("z");

    using SymEngine::sqrt;
    using SymEngine::sub;

#define REQUIRE_SAME(equ1, equ2) REQUIRE(((equ1) == expand((equ2)) || (equ1) == expand(-(equ2))))
    REQUIRE_SAME(SimplifyEquation(sqrt(x * x - 2) - y), x * x - y * y - 2);
    REQUIRE_SAME(SimplifyEquation(sqrt(x * x - 2) - y - z), (y + z) * (y + z) - x * x + 2);
    REQUIRE_SAME(SimplifyEquation(sqrt(x * x - 2) - SymEngine::Expression(SymEngine::pi)),
                 (x * x - 2) - SymEngine::mul(SymEngine::pi, SymEngine::pi));
#undef REQUIRE_SAME
}

} // namespace Algebra

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
#include <symengine/visitor.h>
#include "algebra/util.h"

namespace Algebra {

void Check(const SymEngine::Expression& equation) {
    const auto res = EquationToString(equation).Get(Common::PrintFormat::Plain);
    const u64 pos = res.find("=");
    REQUIRE(pos != std::string::npos);

    SymEngine::Expression left(res.substr(0, pos - 1));
    SymEngine::Expression right(res.substr(pos + 1));

    // 1. Right side has no symbols
    REQUIRE(SymEngine::free_symbols(*right.get_basic()).empty());

    // 2. Equation is same as original
#define REQUIRE_SAME(equ1, equ2) REQUIRE(((equ1) == expand((equ2)) || (equ1) == expand(-(equ2))))
    REQUIRE_SAME(equation, left - right);
#undef REQUIRE_SAME
}

TEST_CASE("EquationToString", "[algebra]") {
    SymEngine::Expression x("x");
    SymEngine::Expression y("y");
    SymEngine::Expression z("z");

    Check(x * x + 2 * y + z + 18);
    Check(-x * x * x - 5);
    Check(x * x * x - y * y * 2 + 7);
    Check(SymEngine::sqrt(x * x - 2) - y * 2 + 3);
    Check(SymEngine::sqrt(x * x - 2) - y - z * 3 + 15);
    Check(SymEngine::sqrt(x * x - 2) - SymEngine::Expression(SymEngine::pi) + 32);
}

} // namespace Algebra

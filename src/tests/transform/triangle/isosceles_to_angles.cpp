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
#include "core/system.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/isosceles_to_angles.h"
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("IsoscelesToAngles", "[transform]") {
    System system;
    system.RegisterTransform<IsoscelesToAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->length_a - triangle->length_b);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(triangle->angle_A - triangle->angle_B).first);
}

TEST_CASE("IsoscelesToAngles[EquilateralTriangle]", "[transform]") {
    System system;
    system.RegisterTransform<IsoscelesToAngles>();
    system.RegisterTransform<TriangleInternalAngles>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto triangle = system.CreateElement<Triangle>("", system, a, b, c);

    system.Algebra().AddEquation(triangle->length_a - SymEngine::integer(3));
    system.Algebra().AddEquation(triangle->length_b - SymEngine::integer(3));
    system.Algebra().AddEquation(triangle->length_c - SymEngine::integer(3));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_A - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_B - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
    REQUIRE(system.Algebra()
                .CheckEquation(triangle->angle_C - SymEngine::Expression(SymEngine::pi) / 3)
                .first);
}

} // namespace Core

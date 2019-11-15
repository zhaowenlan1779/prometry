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
#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TEST_CASE("TriangleInternalAngles", "[transform]") {
    System system;
    system.RegisterTransform<TriangleInternalAngles>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto t = system.CreateElement<Triangle>("", system, p1, p2, p3);

    // Let: A=60 (pi/3), B=30 (pi/6)
    system.Algebra().AddEquation(t->angle_A - SymEngine::Expression(SymEngine::pi) / 3);
    system.Algebra().AddEquation(t->angle_B - SymEngine::Expression(SymEngine::pi) / 6);

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(t->angle_C - SymEngine::Expression(SymEngine::pi) / 2).first);
}

// TODO: More, better tests...

} // namespace Core

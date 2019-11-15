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
#include "geometry/conclusion/line_perpendicular.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/algebra/line_segment_concat.h"
#include "geometry/transform/parallel/perpendicular_to_angles.h"
#include "geometry/transform/pythagorean/pythagorean.h"

namespace Core {

TEST_CASE("PythagoreanSimple", "[transform]") {
    System system;
    system.RegisterTransform<PerpendicularToAngles>();
    system.RegisterTransform<Pythagorean>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");

    p1->AddParent(l1);
    p1->AddParent(l2);
    p2->AddParent(l1);
    p3->AddParent(l2);

    system.CreateElement<Triangle>("", system, p1, p2, p3);
    system.CreateConclusion<LinePerpendicular>("", {}, l1, l2);

    // Let: AB=3 AC=4
    system.Algebra().AddEquation(LineSegmentLength(p1, p2) - SymEngine::integer(3));
    system.Algebra().AddEquation(LineSegmentLength(p1, p3) - SymEngine::integer(4));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(
        system.Algebra().CheckEquation(LineSegmentLength(p2, p3) - SymEngine::integer(5)).first);
}

} // namespace Core

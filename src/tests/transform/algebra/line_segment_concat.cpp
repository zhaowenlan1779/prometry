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
#include "geometry/element/line/line_segment.h"
#include "geometry/transform/algebra/line_segment_concat.h"

namespace Core {

TEST_CASE("LineSegmentConcat", "[transform]") {
    System system;
    system.RegisterTransform<LineSegmentConcat>();
    auto p1 = system.CreateElement<Point>("", "A");
    auto p2 = system.CreateElement<Point>("", "B");
    auto p3 = system.CreateElement<Point>("", "C");
    auto p4 = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l");

    p1->AddParent(l1);
    p2->AddParent(l1);
    p3->AddParent(l1);
    p4->AddParent(l1);

    // Let: AB=3 AC=5
    system.Algebra().AddEquation(LineSegmentLength(p1, p2) - SymEngine::integer(3));
    system.Algebra().AddEquation(LineSegmentLength(p1, p3) - SymEngine::integer(5));

    system.Execute([](System& system) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p2, p3) - SymEngine::integer(2)).first);

    // Let: AD=8
    system.Algebra().AddEquation(LineSegmentLength(p1, p4) - SymEngine::integer(8));

    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p3, p4) - SymEngine::integer(3)).first);
    REQUIRE(system.Algebra().CheckEquation(LineSegmentLength(p2, p4) - SymEngine::integer(5)).first);
}

} // namespace Core

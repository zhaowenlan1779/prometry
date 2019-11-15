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
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/line_parallel_transitivity.h"
#include "geometry/transform/parallel/parallel_to_angles.h"

namespace Core {

TEST_CASE("ParallelToAngles", "[transform]") {
    System system;
    system.RegisterTransform<LineParallelTransitivity>();
    system.RegisterTransform<ParallelToAngles>();
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto l = system.CreateElement<Line>("", "l");
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");
    system.CreateConclusion<LineParallel>("", {}, l1, l2);
    system.CreateConclusion<LineParallel>("", {}, l2, l3);

    p1->AddParent(l1);
    p1->AddParent(l);
    p2->AddParent(l2);
    p2->AddParent(l);
    p3->AddParent(l3);
    p3->AddParent(l);

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.Algebra().CheckEquation(
        LineAngle(l1, LineDirection::Normal, l, LineDirection::Normal) -
        LineAngle(l2, LineDirection::Normal, l, LineDirection::Normal)).first);
    REQUIRE(system.Algebra().CheckEquation(
        LineAngle(l1, LineDirection::Reversed, l, LineDirection::Reversed) -
        LineAngle(l2, LineDirection::Normal, l, LineDirection::Normal)).first);
    REQUIRE(system.Algebra().CheckEquation(
        LineAngle(l1, LineDirection::Reversed, l, LineDirection::Normal) +
        LineAngle(l2, LineDirection::Normal, l, LineDirection::Normal) - SymEngine::pi).first);
}

} // namespace Core

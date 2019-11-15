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
#include "geometry/construction/all_constructions.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/all_transforms.h"

namespace Core {

TEST_CASE("Pythagorean+LineSegmentConcat", "[integrated]") {
    System system;
    RegisterAllTransforms(system);
    RegisterAllConstructions(system);

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    system.CreateConclusion<LinePerpendicular>("hypothesis", {}, l1, l2);

    a->AddParent(l1);
    b->AddParent(l2);
    c->AddParent(l1);
    c->AddParent(l2);
    d->AddParent(l2);

    system.Algebra().AddEquation(LineSegmentLength(a, c) - 1, "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(b, c) - 3, "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(d, b), "hypothesis");

    const auto proof = system.Execute([&a, &d](System& system) {
        const auto& [ret, proof_node] = system.Algebra().CheckEquation(
            LineSegmentLength(a, d) - Algebra::Expression(5) / Algebra::Expression(3));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core

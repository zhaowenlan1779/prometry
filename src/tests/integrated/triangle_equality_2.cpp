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
#include "geometry/construction/all_constructions.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/all_transforms.h"

namespace Core {

TEST_CASE("TriangleEquality_2", "[integrated]") {
    System system;
    RegisterAllTransforms(system);
    RegisterAllConstructions(system);

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");

    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, c), "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(a, b) - LineSegmentLength(a, d), "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(a, c) - LineSegmentLength(a, e), "hypothesis");
    system.Algebra().AddEquation(
        LineAngle(Line::Connect(system, a, b).first, Line::Connect(system, a, d).first).at(0) -
            SymEngine::Expression(SymEngine::pi) / 2,
        "hypothesis");
    system.Algebra().AddEquation(
        LineAngle(Line::Connect(system, a, c).first, Line::Connect(system, a, e).first).at(0) -
            SymEngine::Expression(SymEngine::pi) / 2,
        "hypothesis");

    const auto proof1 = system.Execute([&b, &c, &d, &e](System& system) {
        const auto& [ret, proof_node] =
            system.Algebra().CheckEquation(LineSegmentLength(b, d) - LineSegmentLength(c, e));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof1 << std::endl;
    REQUIRE(!proof1.empty());

    // const auto proof2 = system.Execute([&b, &c, &d, &e](System& system) {
    //     const auto& [bd, dir1] = Line::Connect(system, b, d);
    //     const auto& [bc, dir2] = Line::Connect(system, b, c);
    //     const auto& [ret, proof_node] = system.Algebra().CheckEquation(
    //         LineAngle(bd, dir1, bc, dir2) - 23 * SymEngine::Expression(SymEngine::pi) / 36);
    //     return ret ? proof_node : nullptr;
    // });

    // std::cout << "Proof: " << proof2 << std::endl;
    // REQUIRE(!proof2.empty());
}

} // namespace Core

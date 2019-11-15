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
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/point.h"
#include "geometry/element/triangle.h"
#include "geometry/transform/triangle/sas_similar.h"
#include "geometry/transform/triangle/similar_to_line_segment_ratio.h"

namespace Core {

TEST_CASE("SAS_Similar", "[transform]") {
    System system;
    system.RegisterTransform<SAS_Similar>();
    system.RegisterTransform<SimilarToLineSegmentRatio>();
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");

    const auto& [t1, order1] = MakeTriangle(system, a, b, c);
    const auto& [t2, order2] = MakeTriangle(system, d, e, f);

    // Let: a = 3, b = 4, Angle C = 60
    std::array<Algebra::Expression, 3> edges_1{{t1->length_a, t1->length_b, t1->length_c}};
    ApplyTransform(order1, edges_1);
    system.Algebra().AddEquation(edges_1[0] - SymEngine::integer(3));
    system.Algebra().AddEquation(edges_1[1] - SymEngine::integer(4));

    std::array<Algebra::Expression, 3> angles_1{{t1->angle_A, t1->angle_B, t1->angle_C}};
    ApplyTransform(order1, angles_1);
    system.Algebra().AddEquation(angles_1[2] - SymEngine::Expression(SymEngine::pi) / 3);

    // Let: d = 8, f = 6, Angle E = 60
    std::array<Algebra::Expression, 3> edges_2{{t2->length_a, t2->length_b, t2->length_c}};
    ApplyTransform(order2, edges_2);
    system.Algebra().AddEquation(edges_2[0] - SymEngine::integer(8));
    system.Algebra().AddEquation(edges_2[2] - SymEngine::integer(6));

    std::array<Algebra::Expression, 3> angles_2{{t2->angle_A, t2->angle_B, t2->angle_C}};
    ApplyTransform(order2, angles_2);
    system.Algebra().AddEquation(angles_2[1] - SymEngine::Expression(SymEngine::pi) / 3);

    system.Execute([](System& system) { return nullptr; });

    const auto order3 = MakeTriangle(system, f, d, e).second;

    const auto& similar = system.GetConclusion(TriangleSimilar(t1, order1, t2, order3));
    REQUIRE(similar != nullptr);

    auto ratio = similar->GetRelatedElements()[0] == t1
                     ? SymEngine::Expression(2)
                     : SymEngine::Expression(SymEngine::rational(1, 2));
    REQUIRE(system.Algebra()
                .CheckEquation(
                    std::dynamic_pointer_cast<TriangleSimilar>(similar)->GetSimilarRatio() - ratio)
                .first);
}

// TODO: More, better tests...

} // namespace Core

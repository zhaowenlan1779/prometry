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

#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/sss_similar.h"

namespace Core {

SSS_Similar::SSS_Similar() = default;

SSS_Similar::~SSS_Similar() = default;

/*static*/ void SSS_Similar::Execute(System& system, const std::shared_ptr<Triangle>& t1,
                                     const std::shared_ptr<Triangle>& t2) {

    for (int i = 0; i < TriangleOrders::Count; ++i) {
        std::array<Algebra::Expression, 3> edges{{t1->length_a, t1->length_b, t1->length_c}};
        ApplyTransform(TriangleOrder(i), edges);
        const auto& [ret1, proof_node1] =
            system.Algebra().CheckEquation(t2->length_a / edges[0] - t2->length_b / edges[1]);
        if (!ret1)
            continue;
        const auto& [ret2, proof_node2] =
            system.Algebra().CheckEquation(t2->length_c / edges[2] - t2->length_b / edges[1]);
        if (!ret2)
            continue;
        system.CreateConclusion<TriangleSimilar>("SSS similar", {proof_node1, proof_node2}, t1, t2,
                                                 TriangleOrder(i));
    }
}

} // namespace Core

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
#include "geometry/transform/triangle/aa_similar.h"

namespace Core {

AASimilar::AASimilar() = default;

AASimilar::~AASimilar() = default;

/*static*/ void AASimilar::Execute(System& system, const std::shared_ptr<Triangle>& t1,
                                   const std::shared_ptr<Triangle>& t2) {

    for (int i = 0; i < TriangleOrders::Count; ++i) {
        std::array<Algebra::Expression, 3> angles{{t1->angle_A, t1->angle_B, t1->angle_C}};
        ApplyTransform(TriangleOrder(i), angles);
        const auto& [ret1, proof_node1] = system.Algebra().CheckEquation(angles[0] - t2->angle_A);
        if (!ret1)
            continue;
        const auto& [ret2, proof_node2] = system.Algebra().CheckEquation(angles[1] - t2->angle_B);
        if (!ret2)
            continue;
        system.CreateConclusion<TriangleSimilar>("AA similar", {proof_node1, proof_node2}, t1, t2,
                                                 TriangleOrder(i));
    }
}

} // namespace Core

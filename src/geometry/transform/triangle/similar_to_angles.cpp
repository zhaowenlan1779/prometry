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

#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/transform/triangle/similar_to_angles.h"

namespace Core {

SimilarToAngles::SimilarToAngles() = default;

SimilarToAngles::~SimilarToAngles() = default;

void SimilarToAngles::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::TriangleSimilar)) {
        const auto& similar = std::dynamic_pointer_cast<TriangleSimilar>(conclusion);
        const auto& elements = similar->GetRelatedElements();

        std::array<std::shared_ptr<Triangle>, 2> triangles{
            {std::dynamic_pointer_cast<Triangle>(elements[0]),
             std::dynamic_pointer_cast<Triangle>(elements[1])}};

        std::array<Algebra::Expression, 3> angles{
            {triangles[0]->angle_A, triangles[0]->angle_B, triangles[0]->angle_C}};
        ApplyTransform(similar->GetOrder(), angles);

        system.Algebra().AddEquation(triangles[1]->angle_A - angles[0], "similar to angles",
                                     {similar->GetProofNode()});
        system.Algebra().AddEquation(triangles[1]->angle_B - angles[1], "similar to angles",
                                     {similar->GetProofNode()});
        system.Algebra().AddEquation(triangles[1]->angle_C - angles[2], "similar to angles",
                                     {similar->GetProofNode()});
    }
}

} // namespace Core

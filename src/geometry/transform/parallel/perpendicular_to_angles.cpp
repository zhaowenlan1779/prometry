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
#include "geometry/conclusion/line_perpendicular.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/perpendicular_to_angles.h"

namespace Core {

PerpendicularToAngles::PerpendicularToAngles() = default;

PerpendicularToAngles::~PerpendicularToAngles() = default;

void PerpendicularToAngles::Execute(System& system) {
    for (const auto& conclusion : system.GetConclusions(Conclusions::LinePerpendicular)) {
        const auto& elements = conclusion->GetRelatedElements();

        system.Algebra().AddEquation(
            LineAngle(std::dynamic_pointer_cast<Line>(elements[0]), LineDirection::Normal,
                      std::dynamic_pointer_cast<Line>(elements[1]), LineDirection::Normal) -
                SymEngine::Expression(SymEngine::pi) / 2,
            "perpendicular to angles", {conclusion->GetProofNode()});
    }
}

} // namespace Core

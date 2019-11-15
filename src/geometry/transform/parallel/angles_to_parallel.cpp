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

#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"
#include "geometry/transform/parallel/angles_to_parallel.h"

namespace Core {

AnglesToParallel::AnglesToParallel() = default;

AnglesToParallel::~AnglesToParallel() = default;

/*static*/ void AnglesToParallel::Execute(System& system, const std::shared_ptr<Line>& l,
                                          const std::shared_ptr<Line>& l1,
                                          const std::shared_ptr<Line>& l2) {

    if (Intersection<Point>(l, l1).empty() || Intersection<Point>(l, l2).empty()) {
        return;
    }

    if (!Intersection<Point>(l1, l2).empty()) {
        return;
    }

    const auto& [ret, proof_node] = system.Algebra().CheckEquation(
        LineAngle(l, LineDirection::Normal, l1, LineDirection::Normal) -
        LineAngle(l, LineDirection::Normal, l2, LineDirection::Normal));

    if (ret) {
        system.CreateConclusion<LineParallel>("angles to parallel", {proof_node}, l1, l2);
    }
}

} // namespace Core

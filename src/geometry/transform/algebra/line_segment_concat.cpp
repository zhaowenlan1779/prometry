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

#include "core/system.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/transform/algebra/line_segment_concat.h"

namespace Core {

LineSegmentConcat::LineSegmentConcat() = default;

LineSegmentConcat::~LineSegmentConcat() = default;

/*static*/ void LineSegmentConcat::Execute(System& system, const std::shared_ptr<Line>& line) {
    const auto& points = line->children[Elements::Point];
    for (std::size_t i = 0; i < points.size(); ++i) {
        for (std::size_t j = i + 1; j < points.size(); ++j) {
            for (std::size_t k = j + 1; k < points.size(); ++k) {
                const auto& p1 = std::dynamic_pointer_cast<Point>(points[i].lock());
                const auto& p2 = std::dynamic_pointer_cast<Point>(points[j].lock());
                const auto& p3 = std::dynamic_pointer_cast<Point>(points[k].lock());
                system.Algebra().AddEquation(LineSegmentLength(p1, p2) + LineSegmentLength(p2, p3) -
                                                 LineSegmentLength(p1, p3),
                                             "line segment concat");
            }
        }
    }
}

} // namespace Core

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

#include "algebra/util.h"
#include "common/assert.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/point.h"

namespace Core {

std::string PrettyLineAngleName(const std::shared_ptr<Line>& l1_,
                                const std::shared_ptr<Line>& l2_) {

    const auto& l1 = std::min(l1_, l2_);
    const auto& l2 = std::max(l1_, l2_);

    const auto& points = Intersection<Point>(l1, l2);
    ASSERT_MSG(!points.empty(), "The two lines do not intersect");

    const auto& point = points[0];

    std::string p1_name;
    for (std::size_t i = 0; i < l1->children[Elements::Point].size(); ++i) {
        if (auto iter = l1->children[Elements::Point][i].lock()) {
            if (iter == point) {
                if (i == l1->children[Elements::Point].size() - 1) {
                    return "";
                }
                p1_name = l1->children[Elements::Point][i + 1].lock()->Print();
                break;
            }
        }
    }

    std::string p2_name;
    for (std::size_t i = 0; i < l2->children[Elements::Point].size(); ++i) {
        if (auto iter = l2->children[Elements::Point][i].lock()) {
            if (iter == point) {
                if (i == l2->children[Elements::Point].size() - 1) {
                    return "";
                }
                p2_name = l2->children[Elements::Point][i + 1].lock()->Print();
                break;
            }
        }
    }
    return "angle_" + p1_name + point->Print() + p2_name;
}

std::array<Algebra::Expression, 2> LineAngle(const std::shared_ptr<Line>& l1,
                                             const std::shared_ptr<Line>& l2) {
    ASSERT_MSG(!Intersection<Point>(l1, l2).empty(), "The two lines do not intersect");

    const auto& actual_l1 = std::min(l1, l2);
    const auto& actual_l2 = std::max(l1, l2);

    const auto& symbol =
        SymEngine::symbol(actual_l1->Print() + "_" + actual_l2->Print() + "_angle");
    const auto pretty_name = PrettyLineAngleName(l1, l2);
    if (!pretty_name.empty()) {
        Algebra::RegisterSymbolPrettyName(symbol, pretty_name);
    }

    const auto angle = Algebra::Expression(symbol);
    return {angle, SymEngine::pi - angle};
}

Algebra::Expression LineAngle(const std::shared_ptr<Line>& l1, LineDirection d1,
                              const std::shared_ptr<Line>& l2, LineDirection d2) {
    if (d1 == d2) {
        return LineAngle(l1, l2).at(0);
    } else {
        return LineAngle(l1, l2).at(1);
    }
}

} // namespace Core

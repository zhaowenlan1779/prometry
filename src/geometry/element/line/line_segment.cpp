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

#include "geometry/element/line/line_segment.h"

namespace Core {

Algebra::Expression LineSegmentLength(const std::shared_ptr<Point>& p1_,
                                      const std::shared_ptr<Point>& p2_) {
    const auto& p1 = std::min(p1_, p2_);
    const auto& p2 = std::max(p1_, p2_);

    return Algebra::Expression(SymEngine::symbol(p1->Print() + p2->Print() + "_length"));
}

} // namespace Core

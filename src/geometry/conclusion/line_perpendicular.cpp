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

#include "common/assert.h"
#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_perpendicular.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"

namespace Core {

LinePerpendicular::LinePerpendicular(const std::shared_ptr<Line>& l1_,
                                     const std::shared_ptr<Line>& l2_)
    : l1(std::min(l1_, l2_)), l2(std::max(l1_, l2_)) {}

LinePerpendicular::~LinePerpendicular() = default;

std::string LinePerpendicular::Print(Common::PrintFormat format) const {
    if (format == Common::PrintFormat::Plain) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return line1->Print(format) + " perpendicular " + line2->Print(format);
            }
        }
    } else if (format == Common::PrintFormat::Latex) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return "\\(" + line1->Print(format) + " \\perp " + line2->Print(format) + "\\)";
            }
        }
    }

    UNREACHABLE_MSG("Unexpected!");
}

std::vector<std::shared_ptr<Element>> LinePerpendicular::GetRelatedElements() const {
    return {l1.lock(), l2.lock()};
}

ConclusionType LinePerpendicular::GetType() const {
    return Conclusions::LinePerpendicular;
}

u64 LinePerpendicular::GetHash() const {
    if (auto line1 = l1.lock()) {
        if (auto line2 = l2.lock()) {
            return (line1->GetHash() + line2->GetHash()) * 97 + 3;
        }
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

} // namespace Core

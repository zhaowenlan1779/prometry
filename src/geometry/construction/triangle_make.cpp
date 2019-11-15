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

#include "geometry/construction/triangle_make.h"
#include "geometry/element/line/line.h"
#include "geometry/element/triangle.h"

namespace Core {

TriangleMake::~TriangleMake() = default;

void TriangleMake::Execute(System& system, const std::shared_ptr<Point>& p1,
                           const std::shared_ptr<Point>& p2, const std::shared_ptr<Point>& p3) {

    if (!CommonParent<Line>(p1, p2, p3).empty()) {
        return;
    }

    const auto statement =
        "Declare " + Common::StringPack{/*Plain*/ "Triangle", /*Latex*/ "\\(\\bigtriangleup"} +
        " " + p1->PrintAll() + p2->PrintAll() + p3->PrintAll() +
        Common::StringPack{/*Plain*/ "", /*Latex*/ "\\)"};
    system.CreateElement<Triangle>(statement, system, p1, p2, p3);
}

} // namespace Core

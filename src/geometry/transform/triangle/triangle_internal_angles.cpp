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

#include "geometry/transform/triangle/triangle_internal_angles.h"

namespace Core {

TriangleInternalAngles::TriangleInternalAngles() = default;

TriangleInternalAngles::~TriangleInternalAngles() = default;

/*static*/ void TriangleInternalAngles::Execute(System& system,
                                                const std::shared_ptr<Triangle>& t) {
    system.Algebra().AddEquation(t->angle_A + t->angle_B + t->angle_C - SymEngine::pi,
                                 "triangle internal angles", {});
}

} // namespace Core

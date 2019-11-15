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

#include <catch2/catch.hpp>
#include "core/system.h"
#include "geometry/construction/triangle_make.h"
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

TEST_CASE("TriangleMake", "[construction]") {
    System system;
    system.RegisterConstruction<TriangleMake>();
    auto p1 = system.CreateElement<Point>("", "p1");
    auto p2 = system.CreateElement<Point>("", "p2");
    auto p3 = system.CreateElement<Point>("", "p3");
    auto p4 = system.CreateElement<Point>("", "p4");
    auto p5 = system.CreateElement<Point>("", "p5");

    system.Execute([](System&) { return nullptr; });

    REQUIRE(system.GetElements(Elements::Triangle).size() == 10);
}

} // namespace Core

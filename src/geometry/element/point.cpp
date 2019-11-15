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
#include "geometry/element/element_types.h"
#include "geometry/element/point.h"

namespace Core {

/*static*/ ElementType Point::Type = Elements::Point;

Point::Point(const std::string& name_) : name(name_) {}

Point::~Point() = default;

std::string Point::Print(Common::PrintFormat format) const {
    if (format == Common::PrintFormat::Plain) {
        return name;
    } else if (format == Common::PrintFormat::Latex) {
        return name;
    }

    UNREACHABLE_MSG("Unexpected format!");
}

ElementType Point::GetType() const {
    return Point::Type;
}

u64 Point::GetHash() const {
    return std::hash<std::string>()("Point " + Print());
}

} // namespace Core

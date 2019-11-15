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
#include "common/printer.h"

namespace Common {

StringPack::StringPack() = default;

StringPack::StringPack(const char* c_str) {
    std::string str = c_str;
    std::fill(data.begin(), data.end(), str);
}

StringPack::StringPack(const std::string& str) {
    std::fill(data.begin(), data.end(), str);
}

StringPack::StringPack(const std::initializer_list<std::string>& list) {
    ASSERT(list.size() <= PrintFormatCount);
    for (std::size_t i = 0; i < list.size(); ++i) {
        data[i] = *(list.begin() + i);
    }
    for (std::size_t i = list.size(); i < PrintFormatCount; ++i) {
        // Use plain text as default.
        data[i] = *(list.begin());
    }
}

StringPack::StringPack(std::array<std::string, PrintFormatCount> data_) : data(std::move(data_)) {}

std::string StringPack::Get(PrintFormat format) const {
    return data.at(static_cast<std::size_t>(format));
}

StringPack& StringPack::operator+=(const StringPack& other) {
    for (std::size_t i = 0; i < data.size(); ++i) {
        data[i] += other.data[i];
    }

    return *this;
}

StringPack operator+(const StringPack& lhs, const StringPack& rhs) {
    StringPack ans = lhs;
    ans += rhs;
    return ans;
}

} // namespace Common

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

#pragma once

#include <array>
#include <string>
#include <vector>

namespace Common {

/**
 * Format of the printer used.
 * Implementations of conclusions, elements, etc may or may not implement these formats.
 */
enum class PrintFormat {
    Plain,
    Latex,
};

static constexpr std::size_t PrintFormatCount = 2;

class StringPack {
public:
    // Intentional non-explicit
    StringPack();
    StringPack(const char* c_str);
    StringPack(const std::string& str);
    StringPack(const std::initializer_list<std::string>& list);
    StringPack(std::array<std::string, PrintFormatCount> data);

    StringPack& operator+=(const StringPack& other);
    std::string Get(PrintFormat format) const;

private:
    std::array<std::string, PrintFormatCount> data;
};

StringPack operator+(const StringPack& lhs, const StringPack& rhs);

} // namespace Common

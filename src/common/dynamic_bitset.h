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

#include <vector>
#include "common/common_types.h"

namespace Common {

class DynamicBitset {
public:
    DynamicBitset();
    ~DynamicBitset();

    u64 Size() const;
    u8 At(u64 bit) const;
    void Swap(DynamicBitset& other);

    DynamicBitset& operator|=(const DynamicBitset& other);
    DynamicBitset& operator&=(const DynamicBitset& other);
    DynamicBitset& operator|=(u64 bit_number);
    DynamicBitset& operator&=(u64 bit_number);

private:
    std::vector<u64> data;

    friend DynamicBitset operator&(const DynamicBitset& lhs, const DynamicBitset& rhs);
    friend DynamicBitset operator|(const DynamicBitset& lhs, const DynamicBitset& rhs);
    friend DynamicBitset operator&(const DynamicBitset& lhs, u64 bit_number);
    friend DynamicBitset operator|(const DynamicBitset& lhs, u64 bit_number);
};

DynamicBitset operator&(const DynamicBitset& lhs, const DynamicBitset& rhs);
DynamicBitset operator|(const DynamicBitset& lhs, const DynamicBitset& rhs);
DynamicBitset operator&(const DynamicBitset& lhs, u64 bit_number);
DynamicBitset operator|(const DynamicBitset& lhs, u64 bit_number);

} // namespace Common

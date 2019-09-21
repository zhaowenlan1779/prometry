// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/dynamic_bitset.h"

namespace Common {

DynamicBitset::DynamicBitset() = default;
DynamicBitset::~DynamicBitset() = default;

u64 DynamicBitset::Size() const {
    return data.size() * 8;
}

u8 DynamicBitset::At(u64 bit) const {
    if (Size() <= bit) {
        return 0;
    }
    return (data[bit / 8] >> (bit % 8)) & 1;
}

void DynamicBitset::Swap(DynamicBitset& other) {
    std::swap(data, other.data);
}

DynamicBitset& DynamicBitset::operator|=(const DynamicBitset& other) {
    auto res = *this | other;
    Swap(res);
    return *this;
}

DynamicBitset& DynamicBitset::operator&=(const DynamicBitset& other) {
    auto res = *this & other;
    Swap(res);
    return *this;
}

DynamicBitset& DynamicBitset::operator|=(u64 bit_number) {
    auto res = *this | bit_number;
    Swap(res);
    return *this;
}

DynamicBitset& DynamicBitset::operator&=(u64 bit_number) {
    auto res = *this & bit_number;
    Swap(res);
    return *this;
}

DynamicBitset operator&(const DynamicBitset& lhs, const DynamicBitset& rhs) {
    DynamicBitset ans;
    ans.data.resize(std::min(lhs.data.size(), rhs.data.size()));

    for (std::size_t i = 0; i < ans.data.size(); ++i) {
        ans.data[i] = lhs.data[i] & rhs.data[i];
    }
    return ans;
}

DynamicBitset operator|(const DynamicBitset& lhs, const DynamicBitset& rhs) {
    DynamicBitset ans;
    ans.data.resize(std::max(lhs.data.size(), rhs.data.size()));

    for (std::size_t i = 0; i < ans.data.size(); ++i) {
        ans.data[i] = 0;
        if (i < lhs.data.size())
            ans.data[i] |= lhs.data[i];
        if (i < rhs.data.size())
            ans.data[i] |= rhs.data[i];
    }
    return ans;
}

DynamicBitset operator&(const DynamicBitset& lhs, u64 bit_number) {
    DynamicBitset ans;

    if (bit_number < lhs.Size()) {
        ans.data.resize(bit_number / 8 + 1);
        ans.data[bit_number / 8] = lhs.data[bit_number / 8] & (1 << (bit_number % 8));
    }
    return ans;
}

DynamicBitset operator|(const DynamicBitset& lhs, u64 bit_number) {
    DynamicBitset ans = lhs;
    ans.data.resize(std::max(ans.data.size(), bit_number / 8 + 1));

    ans.data[bit_number / 8] |= 1 << (bit_number % 8);
    return ans;
}

} // namespace Common

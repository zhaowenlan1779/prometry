// Copyright 2019 Zhupengfei and others
// All rights reserved.

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

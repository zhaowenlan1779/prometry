// Copyright 2019 Zhupengfei and others
// All rights reserved.

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

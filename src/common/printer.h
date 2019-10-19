// Copyright 2019 Zhupengfei and others
// All rights reserved.

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

/**
 * Printer template. Default specialization is to call object.Print(format).
 */
template <PrintFormat format, typename T>
struct Printer {
    static std::string Print(const T& object) {
        return object.Print(format);
    }
};

class StringPack {
public:
    // Intentional non-explicit
    StringPack(const std::string& str);
    StringPack(std::array<std::string, PrintFormatCount> data);

    StringPack& operator+=(const StringPack& other);
    std::string Get(PrintFormat format) const;

private:
    std::array<std::string, PrintFormatCount> data;
};

StringPack operator+(const StringPack& lhs, const StringPack& rhs);

} // namespace Common

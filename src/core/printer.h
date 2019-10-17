// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

namespace Core {

/**
 * Format of the printer used.
 * Implementations of conclusions, elements, etc may or may not implement these formats.
 */
enum class PrintFormat {
    Plain,
    Latex,
};

/**
 * Printer template. Default specialization is to call object.PrettyPrint(format).
 */
template <PrintFormat format, typename T>
struct Printer {
    static std::string Print(const T& object) {
        return object.Print(format);
    }
};

} // namespace Core

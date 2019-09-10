// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/conclusion.h"

namespace Core {

namespace Conclusions {
enum ConclusionTypes : ConclusionType {
    Invalid,
    LineParallel,
    LinePrependicular,
    // TODO
};
}

constexpr u64 HashCoeff = 97;

} // namespace Core

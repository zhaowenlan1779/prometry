// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"

namespace Core {

Conclusion::~Conclusion() = default;

bool Conclusion::operator==(const Conclusion& other) const {
    return GetHash() == other.GetHash();
}

bool Conclusion::operator!=(const Conclusion& other) const {
    return GetHash() != other.GetHash();
}

}
// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"
#include "core/element.h"

namespace Core {

bool Element::HasConclusion(const Conclusion& conclusion) const {
    for (auto iter : related_conclusions) {
        if ((*iter) == conclusion)
            return true;
    }
    return false;
}

bool Element::operator==(const Element& other) const {
    return GetHash() == other.GetHash();
}

bool Element::operator!=(const Element& other) const {
    return GetHash() != other.GetHash();
}

} // namespace Core
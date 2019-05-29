// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"
#include "core/element.h"

namespace Core {

/*static*/ ElementType Element::Type = 0;

Element::~Element() = default;

Conclusion* Element::GetConclusion(const Conclusion& conclusion) const {
    for (auto iter : related_conclusions.at(conclusion.GetType())) {
        if ((*iter) == conclusion)
            return iter;
    }
    return nullptr;
}

std::vector<Conclusion*> Element::GetConclusions(ConclusionType type) const {
    return related_conclusions.at(type);
}

bool Element::operator==(const Element& other) const {
    return GetHash() == other.GetHash();
}

bool Element::operator!=(const Element& other) const {
    return GetHash() != other.GetHash();
}

} // namespace Core
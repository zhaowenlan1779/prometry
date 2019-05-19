// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"
#include "core/system.h"

namespace Core {

void System::AddElement(Element* element) {
    auto type = element->GetType();
    if (elements.count(type)) {
        for (auto iter : elements[type]) {
            if ((*iter) == (*element)) {
                return;
            }
        }
    }
    elements[type].emplace_back(element);
}

void System::AddConclusion(Conclusion* conclusion) {
    if (HasConclusion(*conclusion)) {
        return;
    }
    conclusions.emplace_back(conclusion);
    for (auto element : conclusion->GetRelatedElements()) {
        element->related_conclusions.emplace_back(conclusion);
    }
}

bool System::HasConclusion(const Conclusion& conclusion) const {
    for (auto iter : conclusions) {
        if ((*iter) == conclusion)
            return true;
    }
    return false;
}

} // namespace Core
// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"
#include "core/system.h"
#include "core/transform.h"

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
    if (GetConclusion(*conclusion) != nullptr) {
        return;
    }
    conclusions.emplace_back(conclusion);
    for (auto element : conclusion->GetRelatedElements()) {
        element->related_conclusions.emplace_back(conclusion);
    }
    new_conclusion = true;
}

Conclusion* System::GetConclusion(const Conclusion& conclusion) const {
    for (auto iter : conclusions) {
        if ((*iter) == conclusion)
            return iter.get();
    }
    return nullptr;
}

std::string System::Execute(std::function<Conclusion*(System&)> reached_goal_predicate) {
    if (reached_goal_predicate(*this) != nullptr) {
        return "No need to prove";
    }

    Conclusion* target{};

    while (true) {
        for (auto& iter : transforms) {
            iter->Execute(*this);
        }
        if (!new_conclusion) {
            // TODO: construct elements
            break;
        } else if ((target = reached_goal_predicate(*this)) != nullptr) {
            break;
        }
    }

    if (target) {
        // Generate proof content
        std::unordered_map<Conclusion*, bool> visited;
        return GenerateProof(target, visited);
    } else {
        return "";
    }
}

std::string System::GenerateProof(Conclusion* target,
                                  std::unordered_map<Conclusion*, bool>& visited) {

    visited[target] = true;

    // pre-conditions
    std::string proof;
    for (auto iter : target->source_conclusions) {
        if (!visited[iter]) {
            proof += GenerateProof(iter, visited);
        }
    }

    // this statement
    proof += "Because ";
    for (auto iter : target->source_conclusions) {
        proof += iter->ToString() + ",";
    }
    proof += "So " + target->ToString() + "\n";
    return proof;
}

} // namespace Core
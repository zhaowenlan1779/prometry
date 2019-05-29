// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"
#include "core/system.h"
#include "core/transform.h"

namespace Core {

std::vector<std::shared_ptr<Element>> System::GetElements(ElementType type) {
    if (elements.count(type)) {
        return elements.at(type);
    } else {
        return {};
    }
}

void System::AddElement(Element* element, std::string construction_statement) {
    auto type = element->GetType();
    if (elements.count(type)) {
        for (auto iter : elements[type]) {
            if ((*iter) == (*element)) {
                return;
            }
        }
    }
    element->construction_statement = std::move(construction_statement);
    elements[type].emplace_back(element);
    new_element = true;
}

void System::AddConclusion(Conclusion* conclusion, std::string transform_name,
                           std::vector<Conclusion*> source_conclusions) {
    if (GetConclusion(*conclusion) != nullptr) {
        return;
    }
    conclusion->transform_name = std::move(transform_name);
    conclusion->source_conclusions = std::move(source_conclusions);
    conclusions.emplace_back(conclusion);
    for (auto element : conclusion->GetRelatedElements()) {
        element->related_conclusions[conclusion->GetType()].emplace_back(conclusion);
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
        new_conclusion = false;
        for (auto& iter : transforms) {
            iter->Execute(*this);
        }
        if (!new_conclusion) {
            new_element = false;
            for (auto& iter : constructions) {
                iter->Execute(*this);
                if (new_element) { // Try to construct only one at a time
                    break;
                }
            }

            if (!new_element) { // Failed to construct
                break;
            }
        } else if ((target = reached_goal_predicate(*this)) != nullptr) {
            break;
        }
    }

    if (target) {
        // Generate proof content
        std::unordered_map<Conclusion*, bool> visited;
        std::unordered_map<Element*, bool> constructed;
        return GenerateProof(target, visited, constructed);
    } else {
        return "";
    }
}

std::string System::GenerateProof(Conclusion* target,
                                  std::unordered_map<Conclusion*, bool>& visited,
                                  std::unordered_map<Element*, bool>& constructed) {

    visited[target] = true;

    // pre-conditions
    std::string proof;
    for (auto iter : target->source_conclusions) {
        if (!visited[iter]) {
            proof += GenerateProof(iter, visited, constructed);
        }
    }

    // this statement
    for (auto iter : target->GetRelatedElements()) {
        if (!constructed[iter]) {
            constructed[iter] = true;
            if (!iter->construction_statement.empty())
                proof += iter->construction_statement + "\n";
        }
    }

    if (target->source_conclusions.empty()) {
        return proof;
    }

    proof += "Since ";
    for (auto iter : target->source_conclusions) {
        proof += iter->ToString() + ", ";
    }
    proof += "\nSo " + target->ToString() + ". (" + target->transform_name + ")\n";
    return proof;
}

} // namespace Core
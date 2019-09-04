// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "algebra/algebra.h"
#include "core/conclusion.h"
#include "core/system.h"
#include "core/transform.h"

namespace Core {

System::System() : algebra(std::make_unique<Algebra::System>()) {}

System::~System() = default;

Algebra::System& System::Algebra() {
    return *algebra;
}

const Algebra::System& System::Algebra() const {
    return *algebra;
}

std::vector<std::shared_ptr<Element>> System::GetElements(ElementType type) {
    if (elements.count(type)) {
        return elements.at(type);
    } else {
        return {};
    }
}

std::vector<std::shared_ptr<Conclusion>> System::GetConclusions(ConclusionType type) {
    if (conclusions.count(type)) {
        return conclusions.at(type);
    } else {
        return {};
    }
}

std::shared_ptr<Conclusion> System::GetConclusion(const Conclusion& conclusion) const {
    auto type = conclusion.GetType();
    if (!conclusions.count(type))
        return nullptr;
    for (auto iter : conclusions.at(type)) {
        if ((*iter) == conclusion)
            return iter;
    }
    return nullptr;
}

std::string System::Execute(
    std::function<std::shared_ptr<Conclusion>(System&)> reached_goal_predicate) {

    if (reached_goal_predicate(*this) != nullptr) {
        return "No need to prove";
    }

    std::shared_ptr<Conclusion> target{};

    while (true) {
        new_conclusion = false;
        for (auto& iter : transforms) {
            iter->Execute(*this);
        }
        if (!new_conclusion && !algebra->HasNewEquations()) {
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
        std::unordered_set<std::shared_ptr<Conclusion>> visited;
        std::unordered_set<std::shared_ptr<Element>> constructed;
        return GenerateProof(target, visited, constructed);
    } else {
        return "";
    }
}

std::string System::GenerateProof(const std::shared_ptr<Conclusion>& target,
                                  std::unordered_set<std::shared_ptr<Conclusion>>& visited,
                                  std::unordered_set<std::shared_ptr<Element>>& constructed) {

    visited.emplace(target);

    // pre-conditions
    std::string proof;
    for (auto& iter : target->source_conclusions) {
        if (auto ptr = iter.lock()) {
            if (!visited.count(ptr)) {
                proof += GenerateProof(ptr, visited, constructed);
            }
        }
    }

    // this statement
    for (auto& iter : target->GetRelatedElements()) {
        if (!constructed.count(iter)) {
            constructed.emplace(iter);
            if (!iter->construction_statement.empty())
                proof += iter->construction_statement + "\n";
        }
    }

    if (target->source_conclusions.empty()) {
        return proof;
    }

    proof += "Since ";
    for (auto& iter : target->source_conclusions) {
        if (auto ptr = iter.lock())
            proof += ptr->ToString() + ", ";
    }
    proof += "\nSo " + target->ToString() + ". (" + target->transform_name + ")\n";
    return proof;
}

} // namespace Core
// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "core/element.h"

namespace Algebra {
class System;
}

namespace Core {

class Conclusion;
class Transform;
using Construction = Transform;
using ElementType = u8;

/**
 * Definition of the core system, managing elements, conclusions as well
 * as the main logic.
 */
class System {
public:
    explicit System();
    ~System();

    /**
     * Get a reference to the algebra system assoicated to this system.
     */
    Algebra::System& Algebra();

    /**
     * Get a const reference to the algebra system associated to this system.
     */
    const Algebra::System& Algebra() const;

    /**
     * Get elements of a certain type in the System.
     */
    std::vector<std::shared_ptr<Element>> GetElements(ElementType type);

    /**
     * Get conclusions of a certain type in the System.
     */
    std::vector<std::shared_ptr<Conclusion>> GetConclusions(ConclusionType type);

    /**
     * Creates and adds an element to the system, if the conclusion is not already present.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> CreateElement(std::string construction_statement, Args&&... args) {
        static_assert(std::is_base_of_v<Element, T>, "T is not a subclass of Element");

        auto element = std::make_shared<T>(args...);
        if (elements.count(T::Type)) {
            for (const auto& iter : elements[T::Type]) {
                if ((*iter) == (*element)) {
                    return std::dynamic_pointer_cast<T>(iter);
                }
            }
        }
        element->construction_statement = std::move(construction_statement);
        elements[T::Type].emplace_back(element);
        new_element = true;
        return element;
    }

    /**
     * Creates and adds a conclusion to the system, if the conclusion is not already present.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> CreateConclusion(std::string transform_name,
                                        std::vector<std::shared_ptr<Conclusion>> source_conclusions,
                                        Args&&... args) {
        static_assert(std::is_base_of_v<Conclusion, T>, "T is not a subclass of Conclusion");

        auto conclusion = std::make_shared<T>(args...);
        auto cur = GetConclusion(*conclusion);
        if (cur != nullptr) {
            return std::dynamic_pointer_cast<T>(cur);
        }
        conclusion->transform_name = std::move(transform_name);
        for (const auto& iter : source_conclusions) {
            conclusion->source_conclusions.emplace_back(iter);
        }

        auto type = conclusion->GetType();
        conclusions[type].emplace_back(conclusion);
        for (auto& iter : conclusion->GetRelatedElements()) {
            iter->related_conclusions[type].emplace_back(conclusion);
        }
        new_conclusion = true;
        return conclusion;
    }

    /**
     * Register a transform class to the system.
     * The system will initialize and hold a transform object.
     */
    template <typename T>
    void RegisterTransform() {
        static_assert(std::is_base_of_v<Transform, T>, "T is not a subclass of Transform");
        transforms.emplace_back(std::make_unique<T>());
    }

    /**
     * Register a construction class to the system.
     * The system will initialize and hold a construction object.
     */
    template <typename T>
    void RegisterConstruction() {
        static_assert(std::is_base_of_v<Construction, T>, "T is not a subclass of Construction");
        constructions.emplace_back(std::make_unique<T>());
    }

    /// Get a conclusion or nullptr.
    std::shared_ptr<Conclusion> GetConclusion(const Conclusion& conclusion) const;

    /**
     * Executes the main logic.
     *
     * @param reached_goal_predicate function object to judge whether the goal is reached.
     * pointer to target conclusion is returned when the answer is positive, nullptr otherwise
     *
     * @return A string of proof on success, an empty string otherwise
     */
    std::string Execute(std::function<std::shared_ptr<Conclusion>(System&)> reached_goal_predicate);

private:
    std::string GenerateProof(const std::shared_ptr<Conclusion>& target,
                              std::unordered_set<std::shared_ptr<Conclusion>>& visited,
                              std::unordered_set<std::shared_ptr<Element>>& constructed);

    std::unordered_map<ElementType, std::vector<std::shared_ptr<Element>>> elements;
    std::unordered_map<ConclusionType, std::vector<std::shared_ptr<Conclusion>>> conclusions;
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<std::unique_ptr<Construction>> constructions;

    std::unique_ptr<Algebra::System> algebra;

    bool new_element = false;    ///< Temporary state set whenever new elements are constructed.
    bool new_conclusion = false; ///< Temporary state set whenever new conclusions are added.
};

} // namespace Core

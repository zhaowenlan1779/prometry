// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include "core/element.h"

namespace Core {

class Conclusion;
class Transform;
using Construction = Transform;

/**
 * Definition of the core system, managing elements, conclusions as well
 * as the main logic.
 */
class System {
public:
    template <typename T>
    std::vector<std::shared_ptr<Element>> GetElement() {
        if (elements.count(T::Type)) {
            return elements.at(T::Type);
        } else {
            return {};
        }
    }

    /**
     * Add an element to the system, if the element is not already present.
     * WARNING! one shouldn't use the pointer anymore after calling this, as the pointer is
     * now being managed by the system.
     */
    void AddElement(Element* element, std::string construction_statement = "");

    /**
     * Add a conclusion to the system, if the conclusion is not already present.
     * WARNING! one shouldn't use the pointer anymore after calling this, as the pointer is
     * now being managed by the system.
     */
    void AddConclusion(Conclusion* conclusion, std::string transform_name = "",
                       std::vector<Conclusion*> source_conclusions = {});

    /**
     * Register a transform class to the system.
     * The system will initialize and hold a transform object.
     */
    template <typename T>
    void RegisterTransform() {
        transforms.emplace_back(std::make_unique<T>());
    }

    /**
     * Register a construction class to the system.
     * The system will initialize and hold a construction object.
     */
    template <typename T>
    void RegisterConstruction() {
        constructions.emplace_back(std::make_unique<T>());
    }

    /// Get a conclusion or nullptr.
    Conclusion* GetConclusion(const Conclusion& conclusion) const;

    /**
     * Executes the main logic.
     *
     * @param reached_goal_predicate function object to judge whether the goal is reached.
     * pointer to target conclusion is returned when the answer is positive, nullptr otherwise
     *
     * @return A string of proof on success, an empty string otherwise
     */
    std::string Execute(std::function<Conclusion*(System&)> reached_goal_predicate);

private:
    std::string GenerateProof(Conclusion* current, std::unordered_map<Conclusion*, bool>& visited,
                              std::unordered_map<Element*, bool> constructed);

    std::unordered_map<ElementType, std::vector<std::shared_ptr<Element>>> elements;
    std::vector<std::shared_ptr<Conclusion>> conclusions;
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<std::unique_ptr<Construction>> constructions;

    bool new_element = false;    ///< Temporary state set whenever new elements are constructed.
    bool new_conclusion = false; ///< Temporary state set whenever new conclusions are added.
};

} // namespace Core
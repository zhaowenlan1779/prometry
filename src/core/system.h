// Copyright 2019 Zhupengfei and others
// Licensed under the MIT License.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "common/proof_chain_node.h"
#include "core/conclusion.h"
#include "core/element.h"

namespace Algebra {
class System;
}

namespace Core {

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
    std::shared_ptr<T> CreateElement(const Common::StringPack& construction_statement,
                                     Args&&... args) {
        static_assert(std::is_base_of_v<Element, T>, "T is not a subclass of Element");

        auto element = std::make_shared<T>(args...);
        if (elements.count(T::Type)) {
            for (const auto& iter : elements[T::Type]) {
                if ((*iter) == (*element)) {
                    return std::dynamic_pointer_cast<T>(iter);
                }
            }
        }
        element->proof_node = std::make_shared<Common::ProofChainNode>();
        element->proof_node->statement = construction_statement;
        elements[T::Type].emplace_back(element);
        new_element = true;
        return element;
    }

    /**
     * Creates and adds a conclusion to the system, if the conclusion is not already present.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> CreateConclusion(
        const Common::StringPack& transform_name,
        std::vector<std::shared_ptr<Common::ProofChainNode>> source_nodes, Args&&... args) {

        static_assert(std::is_base_of_v<Conclusion, T>, "T is not a subclass of Conclusion");

        auto conclusion = std::make_shared<T>(args...);
        auto cur = GetConclusion(*conclusion);
        if (cur != nullptr) {
            return std::dynamic_pointer_cast<T>(cur);
        }
        conclusion->proof_node = std::make_shared<Common::ProofChainNode>();
        conclusion->proof_node->transform = transform_name;
        conclusion->proof_node->statement = conclusion->PrintAll();
        for (const auto& iter : source_nodes) {
            conclusion->proof_node->reasons.emplace_back(iter);
        }

        auto type = conclusion->GetType();
        conclusions[type].emplace_back(conclusion);
        for (auto& iter : conclusion->GetRelatedElements()) {
            conclusion->proof_node->pre_conditions.emplace_back(iter->proof_node);
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
     * pointer to target proof chain node is returned when the answer is positive, nullptr otherwise
     *
     * @return A string of proof on success, an empty string otherwise
     */
    std::string Execute(
        std::function<std::shared_ptr<Common::ProofChainNode>(System&)> reached_goal_predicate);

private:
    std::unordered_map<ElementType, std::vector<std::shared_ptr<Element>>> elements;
    std::unordered_map<ConclusionType, std::vector<std::shared_ptr<Conclusion>>> conclusions;
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<std::unique_ptr<Construction>> constructions;

    std::unique_ptr<Algebra::System> algebra;

    bool new_element = false;    ///< Temporary state set whenever new elements are constructed.
    bool new_conclusion = false; ///< Temporary state set whenever new conclusions are added.
};

} // namespace Core

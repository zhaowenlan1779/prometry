// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "algebra/algebra.h"
#include "common/common_types.h"
#include "common/printer.h"
#include "common/proof_chain_node.h"

namespace Core {

class Conclusion;
using ConclusionType = u8;

/**
 * Type of the "type" field of an element.
 * Subclasses of Element must provide a static member C::Type.
 */
using ElementType = u8;

enum class Property : u8 {
    Length,
    Angle,
    Area,
    Circumference,
};

/**
 * The element interface.
 *
 * Each element has a name (type not included) and full name (type included).
 * Eg. "AB" and "Line AB".
 *
 * A hash function is used to compare the equality of two elements.
 */
class Element : public std::enable_shared_from_this<Element> {
public:
    static ElementType Type;

    virtual ~Element();

    virtual std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const;

    virtual u64 GetHash() const;

    virtual ElementType GetType() const;

    /// Get a conclusion or nullptr
    std::shared_ptr<Conclusion> GetConclusion(const Conclusion& conclusion) const;

    /// Get conclusions of a type
    std::vector<std::shared_ptr<Conclusion>> GetConclusions(ConclusionType type) const;

    /// Add a parent to this element. The element is automatically added as the parent's child.
    void AddParent(const std::shared_ptr<Element>& parent);

    /// Get a certain algebric property of this element. Throws when not available.
    virtual Algebra::Expression GetProperty(Property property) const;

    // Convenient helpers

    Algebra::Expression Length() const;
    Algebra::Expression Angle() const;
    Algebra::Expression Area() const;
    Algebra::Expression Circumference() const;

    /// Comparison operators
    bool operator==(const Element& other) const;
    bool operator!=(const Element& other) const;

    /// Returns the set of common children (of a single type) of two elements.
    static std::vector<std::shared_ptr<Element>> Intersection(std::shared_ptr<Element> e1,
                                                              std::shared_ptr<Element> e2,
                                                              ElementType type);

    /// Returns the set of common parent (of a single type) of two elements.
    static std::vector<std::shared_ptr<Element>> CommonParent(std::shared_ptr<Element> e1,
                                                              std::shared_ptr<Element> e2,
                                                              ElementType type);

    /*private:*/ // TODO: This is exposed for the Intersection/CommonParent functions below. FIX.

    /// Conclusions related to this element.
    std::unordered_map<ConclusionType, std::vector<std::weak_ptr<Conclusion>>> related_conclusions;
    std::unordered_map<ElementType, std::vector<std::weak_ptr<Element>>> parents;
    std::unordered_map<ElementType, std::vector<std::weak_ptr<Element>>> children;
    std::shared_ptr<Common::ProofChainNode> proof_node;

    friend class System;
};

namespace detail {

template <typename T, typename... Args>
std::vector<std::shared_ptr<T>> Intersection_Impl(std::vector<std::shared_ptr<T>> current,
                                                  const std::shared_ptr<Args>&... args);

template <typename T>
std::vector<std::shared_ptr<T>> Intersection_Impl(std::vector<std::shared_ptr<T>> current) {
    return current;
}

template <typename T, typename Arg, typename... Args>
std::vector<std::shared_ptr<T>> Intersection_Impl(std::vector<std::shared_ptr<T>> current,
                                                  const std::shared_ptr<Arg>& arg,
                                                  const std::shared_ptr<Args>&... args) {
    static_assert(std::is_base_of_v<Element, T>, "T must be a subclass of Element");
    static_assert(std::is_base_of_v<Element, Arg>, "Arguments must be a subclass of Element");

    if (!arg->children.count(T::Type)) {
        return {};
    }

    std::vector<std::shared_ptr<T>> children{arg->children.at(T::Type).size()};
    std::transform(
        arg->children.at(T::Type).begin(), arg->children.at(T::Type).end(), children.begin(),
        [](const std::weak_ptr<Element>& x) { return std::dynamic_pointer_cast<T>(x.lock()); });
    std::sort(children.begin(), children.end());

    current.erase(std::set_intersection(children.begin(), children.end(), current.begin(),
                                        current.end(), current.begin()),
                  current.end());
    return Intersection_Impl<T>(current, args...);
}

template <typename T, typename... Args>
std::vector<std::shared_ptr<T>> CommonParent_Impl(std::vector<std::shared_ptr<T>> current,
                                                  const std::shared_ptr<Args>&... args);

template <typename T>
std::vector<std::shared_ptr<T>> CommonParent_Impl(std::vector<std::shared_ptr<T>> current) {
    return current;
}

template <typename T, typename Arg, typename... Args>
std::vector<std::shared_ptr<T>> CommonParent_Impl(std::vector<std::shared_ptr<T>> current,
                                                  const std::shared_ptr<Arg>& arg,
                                                  const std::shared_ptr<Args>&... args) {
    static_assert(std::is_base_of_v<Element, T>, "T must be a subclass of Element");
    static_assert(std::is_base_of_v<Element, Arg>, "Arguments must be a subclass of Element");

    if (!arg->parents.count(T::Type)) {
        return {};
    }

    std::vector<std::shared_ptr<T>> parents{arg->parents.at(T::Type).size()};
    std::transform(
        arg->parents.at(T::Type).begin(), arg->parents.at(T::Type).end(), parents.begin(),
        [](const std::weak_ptr<Element>& x) { return std::dynamic_pointer_cast<T>(x.lock()); });
    std::sort(parents.begin(), parents.end());

    current.erase(std::set_intersection(parents.begin(), parents.end(), current.begin(),
                                        current.end(), current.begin()),
                  current.end());
    return CommonParent_Impl<T>(current, args...);
}

} // namespace detail

template <typename T, typename Arg, typename... Args>
std::vector<std::shared_ptr<T>> Intersection(const std::shared_ptr<Arg>& arg,
                                             const std::shared_ptr<Args>&... args) {
    static_assert(std::is_base_of_v<Element, T>, "T must be a subclass of Element");
    static_assert(std::is_base_of_v<Element, Arg>, "Arguments must be a subclass of Element");

    if (!arg->children.count(T::Type)) {
        return {};
    }

    std::vector<std::shared_ptr<T>> children{arg->children.at(T::Type).size()};
    std::transform(
        arg->children.at(T::Type).begin(), arg->children.at(T::Type).end(), children.begin(),
        [](const std::weak_ptr<Element>& x) { return std::dynamic_pointer_cast<T>(x.lock()); });
    std::sort(children.begin(), children.end());
    return detail::Intersection_Impl<T>(children, args...);
}

template <typename T, typename Arg, typename... Args>
std::vector<std::shared_ptr<T>> CommonParent(const std::shared_ptr<Arg>& arg,
                                             const std::shared_ptr<Args>&... args) {
    static_assert(std::is_base_of_v<Element, T>, "T must be a subclass of Element");
    static_assert(std::is_base_of_v<Element, Arg>, "Arguments must be a subclass of Element");

    if (!arg->parents.count(T::Type)) {
        return {};
    }

    std::vector<std::shared_ptr<T>> parents{arg->parents.at(T::Type).size()};
    std::transform(
        arg->parents.at(T::Type).begin(), arg->parents.at(T::Type).end(), parents.begin(),
        [](const std::weak_ptr<Element>& x) { return std::dynamic_pointer_cast<T>(x.lock()); });
    std::sort(parents.begin(), parents.end());
    return detail::CommonParent_Impl<T>(parents, args...);
}

} // namespace Core
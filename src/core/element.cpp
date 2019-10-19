// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <exception>
#include "common/proof_chain_node.h"
#include "core/conclusion.h"
#include "core/element.h"

namespace Core {

/*static*/ ElementType Element::Type = 0;

Element::~Element() = default;

std::string Element::Print(Common::PrintFormat format) const {
    return "Unknown";
}

Common::StringPack Element::PrintAll() const {
    return {Print(Common::PrintFormat::Plain), Print(Common::PrintFormat::Latex)};
}

u64 Element::GetHash() const {
    return 0;
}

ElementType Element::GetType() const {
    return 0;
}

std::shared_ptr<Conclusion> Element::GetConclusion(const Conclusion& conclusion) const {
    for (auto& iter : related_conclusions.at(conclusion.GetType())) {
        if (auto ptr = iter.lock()) {
            if ((*ptr) == conclusion) {
                return ptr;
            }
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Conclusion>> Element::GetConclusions(ConclusionType type) const {
    std::vector<std::shared_ptr<Conclusion>> conclusions;
    for (auto& iter : related_conclusions.at(type)) {
        if (auto ptr = iter.lock()) {
            conclusions.emplace_back(ptr);
        }
    }
    return conclusions;
}

void Element::AddParent(const std::shared_ptr<Element>& parent) {
    auto type = parent->GetType();
    for (auto& iter : parents[type]) {
        if (iter.lock() == parent) {
            return;
        }
    }
    parents[type].emplace_back(parent);
    parent->children[GetType()].emplace_back(shared_from_this());
}

Algebra::Expression Element::GetProperty(Property property) const {
    throw std::invalid_argument{"Unimplemented property!"};
}

Algebra::Expression Element::Length() const {
    return GetProperty(Property::Length);
}

Algebra::Expression Element::Angle() const {
    return GetProperty(Property::Angle);
}

Algebra::Expression Element::Area() const {
    return GetProperty(Property::Area);
}

Algebra::Expression Element::Circumference() const {
    return GetProperty(Property::Circumference);
}

bool Element::operator==(const Element& other) const {
    return GetHash() == other.GetHash();
}

bool Element::operator!=(const Element& other) const {
    return GetHash() != other.GetHash();
}

/*static*/ std::vector<std::shared_ptr<Element>> Element::Intersection(std::shared_ptr<Element> e1,
                                                                       std::shared_ptr<Element> e2,
                                                                       ElementType type) {

    std::vector<std::shared_ptr<Element>> e1_children;
    std::transform(e1->children.at(type).begin(), e1->children.at(type).end(), e1_children.begin(),
                   [](const std::weak_ptr<Element>& x) { return x.lock(); });
    std::sort(e1_children.begin(), e1_children.end());

    std::vector<std::shared_ptr<Element>> e2_children;
    std::transform(e2->children.at(type).begin(), e2->children.at(type).end(), e2_children.begin(),
                   [](const std::weak_ptr<Element>& x) { return x.lock(); });
    std::sort(e2_children.begin(), e2_children.end());

    std::vector<std::shared_ptr<Element>> ans;
    std::set_intersection(e1_children.begin(), e1_children.end(), e2_children.begin(),
                          e2_children.end(), ans.begin());

    return ans;
}

/*static*/ std::vector<std::shared_ptr<Element>> Element::CommonParent(std::shared_ptr<Element> e1,
                                                                       std::shared_ptr<Element> e2,
                                                                       ElementType type) {

    std::vector<std::shared_ptr<Element>> e1_parents;
    std::transform(e1->parents.at(type).begin(), e1->parents.at(type).end(), e1_parents.begin(),
                   [](const std::weak_ptr<Element>& x) { return x.lock(); });
    std::sort(e1_parents.begin(), e1_parents.end());

    std::vector<std::shared_ptr<Element>> e2_parents;
    std::transform(e2->parents.at(type).begin(), e2->parents.at(type).end(), e2_parents.begin(),
                   [](const std::weak_ptr<Element>& x) { return x.lock(); });
    std::sort(e2_parents.begin(), e2_parents.end());

    std::vector<std::shared_ptr<Element>> ans;
    std::set_intersection(e1_parents.begin(), e1_parents.end(), e2_parents.begin(),
                          e2_parents.end(), ans.begin());

    return ans;
}

} // namespace Core
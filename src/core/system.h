// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "core/element.h"

namespace Core {

/**
 * Virtual interface for a Geometry System.
 * A System manages Elements as well as Conclusions.
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

    void AddElement(Element* element);
    void AddConclusion(Conclusion* conclusion);

    bool HasConclusion(const Conclusion& conclusion) const;

private:
    std::unordered_map<ElementType, std::vector<std::shared_ptr<Element>>> elements;
    std::vector<std::shared_ptr<Conclusion>> conclusions;
};

} // namespace Core
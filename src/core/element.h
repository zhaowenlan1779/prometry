// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <string>
#include <vector>
#include "common/common_types.h"

namespace Core {

class Conclusion;

/**
 * Type of the "type" field of an element.
 * Subclasses of Element must provide a static member C::Type.
 */
using ElementType = u8;

/**
 * The element interface.
 *
 * Each element has a name (type not included) and full name (type included).
 * Eg. "AB" and "Line AB".
 *
 * A hash function is used to compare the equality of two elements.
 */
class Element {
public:
    static ElementType Type;

    virtual ~Element();

    /**
     * Returns the name (display name) of the element.
     * This can be simpler than the full name, sometimes omitting the type. Eg. "AB" instead of
     * "Line AB" can be used.
     */
    virtual std::string GetName() const {
        return "Unknown";
    }

    /**
     * Returns the full name of the element.
     * Full names should contain the type and name of the element, Eg. "Line AB"
     */
    virtual std::string GetFullname() const {
        return "Unknown Unknown";
    }

    virtual u64 GetHash() const {
        return 0;
    }

    virtual ElementType GetType() const {
        return 0;
    }

    /// Get a conclusion or nullptr
    Conclusion* GetConclusion(const Conclusion& conclusion) const;

    /// Comparison operators
    bool operator==(const Element& e) const;
    bool operator!=(const Element& e) const;

private:
    std::vector<Conclusion*> related_conclusions; ///< Conclusions related to this element.
    std::string construction_statement;           ///< Construction statement for this element.

    friend class System;
};

} // namespace Core
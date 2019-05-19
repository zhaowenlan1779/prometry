// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <string>
#include <vector>
#include "common/common_types.h"

namespace Core {

class Element;
class Transform;

/**
 * Virtual interface for conclusions.
 * A hash function is used to compare the equality of two conclusions.
 */
class Conclusion {
public:
    virtual ~Conclusion();

    /**
     * Output the string for this conclusion. E.g. "AB // CD".
     */
    virtual std::string ToString() const {
        return "Unknown";
    }

    /**
     * Get the elements related to this conclusion.
     * When adding this conclusion to the system, the elements related will be updated as well.
     */
    virtual std::vector<Element*> GetRelatedElements() = 0;

    virtual u64 GetHash() const = 0;

    /// Comparison operators
    bool operator==(const Conclusion& other) const;
    bool operator!=(const Conclusion& other) const;

protected:
    std::vector<Conclusion*> source_conclusions; ///< The conclusions this conclusion is based on.
    Transform* transform;                        ///< The transform that created this conclusion.

    friend class System;
};

} // namespace Core
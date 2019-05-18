// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <vector>

namespace Core {

/**
 * Virtual interface for a Geometry System.
 * A System manages Elements as well as Conclusions.
 */
class System {
public:
    template <typename T>
    std::vector<T> GetElement();
};

} // namespace Core
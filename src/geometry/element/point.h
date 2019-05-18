// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point : public Element {
public:
    explicit Point(const std::string& name);
    std::string GetName() const override;
    std::string GetFullname() const override;
    u64 GetHash() const override;

private:
    std::string name;
};

}
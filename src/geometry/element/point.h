// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point : public Element {
public:
    static ElementType Type;

    explicit Point(const std::string& name);
    ~Point() override;
    std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const override;
    ElementType GetType() const override;
    u64 GetHash() const override;

private:
    std::string name;
};

} // namespace Core
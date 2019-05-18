// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point;

class Line : public Element {
public:
    explicit Line(const Point& p1, const Point& p2);
    std::string GetName() const override;
    std::string GetFullname() const override;
    u64 GetHash() const override;

private:
    const Point& p1;
    const Point& p2;
};

}
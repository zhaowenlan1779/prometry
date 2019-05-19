// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point;

class Line : public Element {
public:
    static ElementType Type;

    explicit Line(const Point& p1, const Point& p2);
    ~Line() override;
    std::string GetName() const override;
    std::string GetFullname() const override;
    ElementType GetType() const override;
    u64 GetHash() const override;

private:
    const Point& p1;
    const Point& p2;
};

}
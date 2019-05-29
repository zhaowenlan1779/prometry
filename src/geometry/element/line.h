// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point;

class Line : public Element {
public:
    static ElementType Type;

    ElementType GetType() const override;
};

class TwoPointsLine : public Line {
public:
    explicit TwoPointsLine(const Point& p1, const Point& p2);
    ~TwoPointsLine() override;
    std::string GetName() const override;
    std::string GetFullname() const override;
    u64 GetHash() const override;

private:
    const Point& p1;
    const Point& p2;
};

class StandaloneLine : public Line {
public:
    explicit StandaloneLine(const std::string& name);
    ~StandaloneLine() override;
    std::string GetName() const override;
    std::string GetFullname() const override;
    u64 GetHash() const override;

private:
    std::string name;
};

} // namespace Core

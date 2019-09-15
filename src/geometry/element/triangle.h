// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include "core/element.h"

namespace Core {

class Point;
class Line;
class System;

class Triangle : public Element {
public:
    static ElementType Type;

    explicit Triangle(System& system, const std::shared_ptr<Point>& A,
                      const std::shared_ptr<Point>& B, const std::shared_ptr<Point>& C);
    ~Triangle() override;
    std::string GetName() const override;
    std::string GetFullname() const override;
    ElementType GetType() const override;
    u64 GetHash() const override;

    std::shared_ptr<Point> A, B, C;
    std::shared_ptr<Line> a, b, c;
    Algebra::Expression angle_A, angle_B, angle_C;
    Algebra::Expression length_a, length_b, length_c;
};

} // namespace Core

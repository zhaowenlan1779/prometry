// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/element.h"

namespace Core {

class Point;
class System;

enum class LineDirection {
    Normal,   ///< Starting from first child point
    Reversed, ///< Starting from last child point
};

class Line : public Element {
public:
    static ElementType Type;

    explicit Line(const std::string& name);
    ~Line() override;
    std::string Print(PrintFormat format = PrintFormat::Plain) const override;
    ElementType GetType() const override;
    u64 GetHash() const override;
    LineDirection GetLineDirection(const std::shared_ptr<Point>& p1,
                                   const std::shared_ptr<Point>& p2) const;

    /**
     * Returns the line that connects the two points.
     * If such a line already exists, returns that line. Otherwise create a new one with the two
     * points added as children.
     */
    static std::pair<std::shared_ptr<Line>, LineDirection> Connect(
        System& system, const std::shared_ptr<Point>& p1, const std::shared_ptr<Point>& p2);

private:
    std::string name;
};

} // namespace Core

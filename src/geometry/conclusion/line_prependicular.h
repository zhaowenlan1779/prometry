// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include "core/conclusion.h"

namespace Core {

class Element;
class Line;

class LinePrependicular : public Conclusion {
public:
    explicit LinePrependicular(const std::shared_ptr<Line>& l1, const std::shared_ptr<Line>& l2);
    ~LinePrependicular() override;
    std::string Print(PrintFormat format = PrintFormat::Plain) const override;
    std::vector<std::shared_ptr<Element>> GetRelatedElements() const override;
    ConclusionType GetType() const override;
    u64 GetHash() const override;

private:
    std::weak_ptr<Element> l1;
    std::weak_ptr<Element> l2;
};

} // namespace Core

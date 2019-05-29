// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/conclusion.h"

namespace Core {

class Element;

class LineParallel : public Conclusion {
public:
    explicit LineParallel(Element& l1, Element& l2);
    ~LineParallel() override;
    std::string ToString() const override;
    std::vector<Element*> GetRelatedElements() const override;
    ConclusionType GetType() const override;
    u64 GetHash() const override;

private:
    Element& l1;
    Element& l2;
};

} // namespace Core

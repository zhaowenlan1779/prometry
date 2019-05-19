// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/conclusion.h"

namespace Core {

class Line;

class LineParallel : public Conclusion {
public:
    explicit LineParallel(Line& l1, Line& l2);
    ~LineParallel() override;
    std::string ToString() const override;
    std::vector<Element*> GetRelatedElements() override;
    u64 GetHash() const override;

private:
    Line& l1;
    Line& l2;
};

}
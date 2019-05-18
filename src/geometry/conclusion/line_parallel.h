// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include "core/conclusion.h"

namespace Core {

class Line;

class LineParallel : public Conclusion {
public:
    explicit LineParallel(const Line& l1, const Line& l2);
    std::string ToString() const override;
    std::vector<const Element*> GetRelatedElements() const override;
    u64 GetHash() const override;

private:
    const Line& l1;
    const Line& l2;
};

}
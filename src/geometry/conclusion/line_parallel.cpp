// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"

namespace Core {

LineParallel::LineParallel(const Line& l1_, const Line& l2_) : l1(l1_), l2(l2_) {}

std::string LineParallel::ToString() const {
    return l1.GetName() + " // " + l2.GetName();
}

std::vector<const Element*> LineParallel::GetRelatedElements() const {
    return {&l1, &l2};
}

u64 LineParallel::GetHash() const {
    return (l1.GetHash() + l2.GetHash()) * 97 + 2;
}

} // namespace Core
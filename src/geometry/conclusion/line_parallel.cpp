// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line.h"

namespace Core {

LineParallel::LineParallel(Line& l1_, Line& l2_) : l1(l1_), l2(l2_) {}

LineParallel::~LineParallel() = default;

std::string LineParallel::ToString() const {
    return l1.GetName() + " // " + l2.GetName();
}

std::vector<Element*> LineParallel::GetRelatedElements() {
    return {&l1, &l2};
}

u64 LineParallel::GetHash() const {
    return (l1.GetHash() + l2.GetHash()) * 97 + 2;
}

} // namespace Core
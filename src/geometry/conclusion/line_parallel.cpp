// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"

namespace Core {

LineParallel::LineParallel(const std::shared_ptr<Line>& l1_, const std::shared_ptr<Line>& l2_)
    : l1(std::min(l1_, l2_)), l2(std::max(l1_, l2_)) {}

LineParallel::~LineParallel() = default;

std::string LineParallel::Print(PrintFormat format) const {
    if (format == PrintFormat::Plain) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return line1->Print(format) + " // " + line2->Print(format);
            }
        }
    } else if (format == PrintFormat::Latex) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return line1->Print(format) + " \\parallel " + line2->Print(format);
            }
        }
    }

    UNREACHABLE_MSG("Unexpected!");
}

std::vector<std::shared_ptr<Element>> LineParallel::GetRelatedElements() const {
    return {l1.lock(), l2.lock()};
}

ConclusionType LineParallel::GetType() const {
    return Conclusions::LineParallel;
}

u64 LineParallel::GetHash() const {
    if (auto line1 = l1.lock()) {
        if (auto line2 = l2.lock()) {
            return (line1->GetHash() + line2->GetHash()) * 97 + 2;
        }
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

} // namespace Core
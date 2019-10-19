// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/line_prependicular.h"
#include "geometry/element/element_types.h"
#include "geometry/element/line/line.h"

namespace Core {

LinePrependicular::LinePrependicular(const std::shared_ptr<Line>& l1_,
                                     const std::shared_ptr<Line>& l2_)
    : l1(std::min(l1_, l2_)), l2(std::max(l1_, l2_)) {}

LinePrependicular::~LinePrependicular() = default;

std::string LinePrependicular::Print(Common::PrintFormat format) const {
    if (format == Common::PrintFormat::Plain) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return line1->Print(format) + " prependicular " + line2->Print(format);
            }
        }
    } else if (format == Common::PrintFormat::Latex) {
        if (auto line1 = l1.lock()) {
            if (auto line2 = l2.lock()) {
                return line1->Print(format) + " \\perp " + line2->Print(format);
            }
        }
    }

    UNREACHABLE_MSG("Unexpected!");
}

std::vector<std::shared_ptr<Element>> LinePrependicular::GetRelatedElements() const {
    return {l1.lock(), l2.lock()};
}

ConclusionType LinePrependicular::GetType() const {
    return Conclusions::LinePrependicular;
}

u64 LinePrependicular::GetHash() const {
    if (auto line1 = l1.lock()) {
        if (auto line2 = l2.lock()) {
            return (line1->GetHash() + line2->GetHash()) * 97 + 3;
        }
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

} // namespace Core

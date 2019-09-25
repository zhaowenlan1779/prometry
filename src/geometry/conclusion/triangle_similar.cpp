// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "common/assert.h"
#include "geometry/conclusion/conclusion_types.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/element/point.h"

namespace Core {

TriangleSimilar::TriangleSimilar(const std::shared_ptr<Triangle>& t1_, TriangleOrder order1,
                                 const std::shared_ptr<Triangle>& t2_, TriangleOrder order2)
    : t1(std::min(t1_, t2_)), t2(std::max(t1_, t2_)) {

    order = (t1.lock() == t1_) ? GetRelativeTriangleOrder(order1, order2)
                               : GetRelativeTriangleOrder(order2, order1);

    ratio = Algebra::Expression(
        SymEngine::symbol(t1.lock()->GetName() + "_" + GetTriangle2Text() + "_similar_k"));
}

TriangleSimilar::~TriangleSimilar() = default;

std::string TriangleSimilar::GetTriangle2Text() const {
    if (auto triangle2 = t2.lock()) {
        std::array<std::shared_ptr<Point>, 3> points{{triangle2->A, triangle2->B, triangle2->C}};
        ApplyTransform(order, points);
        return points[0]->GetName() + points[1]->GetName() + points[2]->GetName();
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

std::string TriangleSimilar::ToString() const {
    if (auto triangle1 = t1.lock()) {
        return triangle1->GetName() + " similar " + GetTriangle2Text();
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

std::vector<std::shared_ptr<Element>> TriangleSimilar::GetRelatedElements() const {
    return {t1.lock(), t2.lock()};
}

ConclusionType TriangleSimilar::GetType() const {
    return Conclusions::TriangleSimilar;
}

u64 TriangleSimilar::GetHash() const {
    if (auto triangle1 = t1.lock()) {
        if (auto triangle2 = t2.lock()) {
            return ((triangle1->GetHash() + triangle2->GetHash()) * 97 + order) * 97 + 4;
        }
    }
    UNREACHABLE_MSG("Unexpected expired weak_ptr!");
}

TriangleOrder TriangleSimilar::GetOrder() const {
    return order;
}

Algebra::Expression TriangleSimilar::GetSimilarRatio() const {
    return ratio;
}

} // namespace Core

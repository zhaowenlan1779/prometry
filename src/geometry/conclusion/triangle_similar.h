// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include "algebra/algebra.h"
#include "core/conclusion.h"
#include "geometry/element/triangle.h"

namespace Core {

class TriangleSimilar : public Conclusion {
public:
    explicit TriangleSimilar(const std::shared_ptr<Triangle>& t1, TriangleOrder order1,
                             const std::shared_ptr<Triangle>& t2, TriangleOrder order2);
    ~TriangleSimilar() override;
    std::string ToString() const override;
    std::vector<std::shared_ptr<Element>> GetRelatedElements() const override;
    ConclusionType GetType() const override;
    u64 GetHash() const override;

    TriangleOrder GetOrder() const;
    Algebra::Expression GetSimilarRatio() const;

private:
    std::string GetTriangle2Text() const;

    std::weak_ptr<Triangle> t1;
    std::weak_ptr<Triangle> t2;

    TriangleOrder order;
    Algebra::Expression ratio;
};

} // namespace Core

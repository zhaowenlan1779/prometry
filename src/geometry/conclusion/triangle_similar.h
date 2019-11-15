// Copyright 2019 Zhupengfei and others
// Licensed under the MIT License.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    explicit TriangleSimilar(const std::shared_ptr<Triangle>& t1,
                             const std::shared_ptr<Triangle>& t2, TriangleOrder order);
    ~TriangleSimilar() override;
    std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const override;
    std::vector<std::shared_ptr<Element>> GetRelatedElements() const override;
    ConclusionType GetType() const override;
    u64 GetHash() const override;

    TriangleOrder GetOrder() const;
    Algebra::Expression GetSimilarRatio() const;

private:
    std::string GetTriangle1Text(Common::PrintFormat format = Common::PrintFormat::Plain) const;

    std::weak_ptr<Triangle> t1;
    std::weak_ptr<Triangle> t2;

    /// This order means: t1 applied 'order' transform is similar to t2.
    TriangleOrder order;
    Algebra::Expression ratio;
};

} // namespace Core

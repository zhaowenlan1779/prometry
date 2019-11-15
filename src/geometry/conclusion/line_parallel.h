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
#include "core/conclusion.h"

namespace Core {

class Element;
class Line;

class LineParallel : public Conclusion {
public:
    explicit LineParallel(const std::shared_ptr<Line>& l1, const std::shared_ptr<Line>& l2);
    ~LineParallel() override;
    std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const override;
    std::vector<std::shared_ptr<Element>> GetRelatedElements() const override;
    ConclusionType GetType() const override;
    u64 GetHash() const override;

private:
    std::weak_ptr<Element> l1;
    std::weak_ptr<Element> l2;
};

} // namespace Core

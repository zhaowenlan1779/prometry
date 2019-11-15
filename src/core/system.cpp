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

#include "algebra/algebra.h"
#include "core/conclusion.h"
#include "core/system.h"
#include "core/transform.h"

namespace Core {

System::System() : algebra(std::make_unique<Algebra::System>()) {}

System::~System() = default;

Algebra::System& System::Algebra() {
    return *algebra;
}

const Algebra::System& System::Algebra() const {
    return *algebra;
}

std::vector<std::shared_ptr<Element>> System::GetElements(ElementType type) {
    if (elements.count(type)) {
        return elements.at(type);
    } else {
        return {};
    }
}

std::vector<std::shared_ptr<Conclusion>> System::GetConclusions(ConclusionType type) {
    if (conclusions.count(type)) {
        return conclusions.at(type);
    } else {
        return {};
    }
}

std::shared_ptr<Conclusion> System::GetConclusion(const Conclusion& conclusion) const {
    auto type = conclusion.GetType();
    if (!conclusions.count(type))
        return nullptr;
    for (auto iter : conclusions.at(type)) {
        if ((*iter) == conclusion)
            return iter;
    }
    return nullptr;
}

std::string System::Execute(
    std::function<std::shared_ptr<Common::ProofChainNode>(System&)> reached_goal_predicate) {

    if (reached_goal_predicate(*this) != nullptr) {
        return "No need to prove";
    }

    std::shared_ptr<Common::ProofChainNode> target{};

    while (true) {
        new_conclusion = false;
        for (auto& iter : transforms) {
            iter->Execute(*this);
            if ((target = reached_goal_predicate(*this)) != nullptr) {
                goto completed;
            }
        }
        if (!new_conclusion && !algebra->HasNewEquations()) {
            new_element = false;
            for (auto& iter : constructions) {
                iter->Execute(*this);
                if (new_element) { // Try to construct only one at a time
                    break;
                }
            }

            if (!new_element) { // Failed to construct
                break;
            }
        }
    }

completed:
    if (target) {
        // Generate proof content
        return Common::GenerateProof(target);
    } else {
        return "";
    }
}

} // namespace Core
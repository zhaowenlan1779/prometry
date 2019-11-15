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

#include "geometry/transform/pythagorean/pythagorean.h"

namespace Core {

Pythagorean::Pythagorean() = default;

Pythagorean::~Pythagorean() = default;

/*static*/ void Pythagorean::Execute(System& system, const std::shared_ptr<Triangle>& t) {
#define CHECK(angle, long, short1, short2)                                                         \
    {                                                                                              \
        const auto& [ret, proof_list] =                                                            \
            system.Algebra().CheckEquation(t->angle - SymEngine::Expression(SymEngine::pi) / 2);   \
        if (ret) {                                                                                 \
            system.Algebra().AddEquation(t->short1 * t->short1 + t->short2 * t->short2 -           \
                                             t->long * t->long,                                    \
                                         "pythagorean theroem", {proof_list});                     \
        }                                                                                          \
    }

    CHECK(angle_A, length_a, length_b, length_c);
    CHECK(angle_B, length_b, length_a, length_c);
    CHECK(angle_C, length_c, length_a, length_b);
#undef CHECK
}

} // namespace Core

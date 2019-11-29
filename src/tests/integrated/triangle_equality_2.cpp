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

#include <catch2/catch.hpp>
#include "geometry/prospec.h"

namespace Core {

TEST_CASE("TriangleEquality_2", "[integrated]") {
    prospec_begin;

    point(A, B, C, D, E);
    line(AB, A, B);
    line(AD, A, D);
    line(AC, A, C);
    line(AE, A, E);

    equation(len(A, B) - len(A, C));
    equation(len(A, B) - len(A, D));
    equation(len(A, C) - len(A, E));
    equation(angle(AB, AD).at(0) - pi / 2);
    equation(angle(AC, AE).at(0) - pi / 2);

    const auto proof1 = execute_single(len(B, D) - len(C, E));
    std::cout << "Proof: " << proof1 << std::endl;
    REQUIRE(!proof1.empty());

    // const auto proof2 = system.Execute([&b, &c, &d, &e](System& system) {
    //     const auto& [bd, dir1] = Line::Connect(system, b, d);
    //     const auto& [bc, dir2] = Line::Connect(system, b, c);
    //     const auto& [ret, proof_node] = system.Algebra().CheckEquation(
    //         LineAngle(bd, dir1, bc, dir2) - 23 * SymEngine::Expression(SymEngine::pi) / 36);
    //     return ret ? proof_node : nullptr;
    // });

    // std::cout << "Proof: " << proof2 << std::endl;
    // REQUIRE(!proof2.empty());
    prospec_end;
}

} // namespace Core

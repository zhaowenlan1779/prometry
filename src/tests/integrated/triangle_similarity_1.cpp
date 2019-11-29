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

TEST_CASE("TriangleSimilarity_1", "[integrated]") {
    // Problem available https://wenku.baidu.com/view/77631515f705cc1754270999.html as 2-8.

    prospec_begin;

    point(A, B, C, D, E, F, G, M);
    line(AC, A, C);
    line(AE, A, F, E);
    line(AD, A, G, D);
    line(AB, A, M, B);
    line(CM, C, F, G, M);
    line(BC, B, D, E, C);

    equation(len(B, D) - len(D, E));
    equation(len(D, E) - len(E, C));
    equation(len(A, M) - len(M, B));

    const auto proof = execute_multiple(
        str("CF:FG:GM = 5:3:2", "\\(\\overline{CF} : \\overline{FG} : \\overline{GM} = 5:3:2\\)"),
        "algebra", len(C, F) / len(F, G) - frac(5, 3), len(F, G) / len(G, M) - frac(3, 2));
    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());

    prospec_end;
}

} // namespace Core

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

TEST_CASE("TriangleSimilarity_2", "[integrated]") {
    // Problem available https://wenku.baidu.com/view/77631515f705cc1754270999.html as 2-11.

    prospec_begin;

    point(A, B, C, D, E, F, G);
    line(BC, B, C);
    line(AD, A, F, D);
    line(AC, A, E, C);
    line(BG, B, E, F, G);
    line(CG, C, D, G);
    line(AB, A, B);
    
    line_parallel(AD, BC);
    line_parallel(AB, CG);
    equation(len(A, D) - len(B, C));
    equation(len(A, E) / len(E, C) - frac(1, 3));
    equation(len(A, B) - len(C, D));

    const auto proof = execute_single(len(B, F) / len(F, G) - frac(1, 2));
    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());

    prospec_end;
}

} // namespace Core

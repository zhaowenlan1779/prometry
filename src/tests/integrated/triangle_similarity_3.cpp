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

TEST_CASE("TriangleSimilarity_3", "[integrated]") {
    // Problem available https://wenku.baidu.com/view/71781cef591b6bd97f192279168884868662b828.html
    // as 18.

    prospec_begin;

    point(A, B, C, D, E);
    line(BC, B, D, C);
    line(AB, A, E, B);
    line(AC, A, C);
    line(AD, A, D);
    line(CE, C, E);

    equation(len(B, D) - len(D, C));
    equation(len(A, E) - len(E, B));
    equation(angle(AB, AD).at(0) - angle(BC, CE).at(1));

    const auto proof = execute_single(len(A, B) - len(B, C));
    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());

    prospec_end;
}

} // namespace Core

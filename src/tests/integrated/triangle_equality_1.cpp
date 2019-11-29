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

TEST_CASE("TriangleEquality_1", "[integrated]") {
    prospec_begin;

    point(A, B, C, D, E);
    line(l, D, B, C, E);

    equation(len(A, B) - len(A, C));
    equation(len(A, D) - len(A, E));

    const auto proof = execute_single(len(B, D) - len(C, E));
    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());

    prospec_end;
}

} // namespace Core

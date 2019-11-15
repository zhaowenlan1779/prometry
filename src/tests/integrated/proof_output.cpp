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
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/element/line/line.h"
#include "geometry/transform/all_transforms.h"

#include <iostream>

namespace Core {

TEST_CASE("ProofOutput[LineParallelTransitivity]", "[integrated]") {
    System system;
    RegisterAllTransforms(system);

    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    auto l3 = system.CreateElement<Line>("", "l3");
    auto l4 = system.CreateElement<Line>("", "l4");
    system.CreateConclusion<LineParallel>("hypothesis", {}, l1, l2);
    system.CreateConclusion<LineParallel>("hypothesis", {}, l2, l3);
    system.CreateConclusion<LineParallel>("hypothesis", {}, l3, l4);

    const auto proof = system.Execute([&l1, &l4](System& system) {
        auto conclusion = system.GetConclusion(LineParallel(l1, l4));
        return conclusion ? conclusion->GetProofNode() : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core
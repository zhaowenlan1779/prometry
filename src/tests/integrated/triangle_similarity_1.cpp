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
#include "geometry/construction/all_constructions.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/all_transforms.h"

namespace Core {

TEST_CASE("TriangleSimilarity_1", "[integrated]") {
    // Problem available https://wenku.baidu.com/view/77631515f705cc1754270999.html as 2-8.

    System system;
    RegisterAllTransforms(system);
    RegisterAllConstructions(system);

    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto e = system.CreateElement<Point>("", "E");
    auto f = system.CreateElement<Point>("", "F");
    auto g = system.CreateElement<Point>("", "G");
    auto m = system.CreateElement<Point>("", "M");
    auto ac = system.CreateElement<Line>("", "AC");
    auto ae = system.CreateElement<Line>("", "AE");
    auto ad = system.CreateElement<Line>("", "AD");
    auto ab = system.CreateElement<Line>("", "AB");
    auto cm = system.CreateElement<Line>("", "CM");
    auto bc = system.CreateElement<Line>("", "BC");

    a->AddParent(ac);
    c->AddParent(ac);

    a->AddParent(ae);
    f->AddParent(ae);
    e->AddParent(ae);

    a->AddParent(ad);
    g->AddParent(ad);
    d->AddParent(ad);

    a->AddParent(ab);
    m->AddParent(ab);
    b->AddParent(ab);

    c->AddParent(cm);
    f->AddParent(cm);
    g->AddParent(cm);
    m->AddParent(cm);

    b->AddParent(bc);
    d->AddParent(bc);
    e->AddParent(bc);
    c->AddParent(bc);

    system.Algebra().AddEquation(LineSegmentLength(b, d) - LineSegmentLength(d, e), "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(d, e) - LineSegmentLength(e, c), "hypothesis");
    system.Algebra().AddEquation(LineSegmentLength(a, m) - LineSegmentLength(m, b), "hypothesis");

    const auto proof =
        system.Execute([&c, &f, &g, &m, /* to_erase*/ &a,
                        &d](System& system) -> std::shared_ptr<Common::ProofChainNode> {
            const auto& [ret1, proof_node1] = system.Algebra().CheckEquation(
                LineSegmentLength(c, f) / LineSegmentLength(f, g) - SymEngine::rational(5, 3));
            if (!ret1)
                return nullptr;

            const auto& [ret2, proof_node2] = system.Algebra().CheckEquation(
                LineSegmentLength(f, g) / LineSegmentLength(g, m) - SymEngine::rational(3, 2));
            if (!ret2)
                return nullptr;

            const auto& proof_node = std::make_shared<Common::ProofChainNode>();
            proof_node->statement = {
                /*Plain*/ "CF:FG:GM = 5:3:2",
                /*Latex*/ "\\(\\overline{CF} : \\overline{FG} : \\overline{GM} = 5:3:2\\)"};
            proof_node->transform = "algebra";
            proof_node->reasons.emplace_back(proof_node1);
            proof_node->reasons.emplace_back(proof_node2);

            return proof_node;
        });

    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());
}

} // namespace Core

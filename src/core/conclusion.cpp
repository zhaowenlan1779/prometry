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

#include "core/conclusion.h"

namespace Core {

Conclusion::~Conclusion() = default;

std::string Conclusion::Print(Common::PrintFormat format) const {
    return "Unknown";
}

Common::StringPack Conclusion::PrintAll() const {
    return {Print(Common::PrintFormat::Plain), Print(Common::PrintFormat::Latex)};
}

bool Conclusion::operator==(const Conclusion& other) const {
    return GetHash() == other.GetHash();
}

bool Conclusion::operator!=(const Conclusion& other) const {
    return GetHash() != other.GetHash();
}

std::shared_ptr<Common::ProofChainNode> Conclusion::GetProofNode() const {
    return proof_node;
}

}
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

#pragma once

#include <unordered_set>
#include "common/common_types.h"
#include "core/system.h"

namespace Core {

/**
 * Virtual interface for transforms.
 *
 * Transforms are generalized templates that consist of axioms, thereoms and common models,
 * which can be used in the proof. (common models will get expanded)
 */
class Transform {
public:
    virtual ~Transform() = default;
    virtual void Execute(System& system) = 0;
};

/**
 * Virtual interface for constructions.
 *
 * Constructions are generalized templates used to construct additional elements besides those
 * already present.
 */
using Construction = Transform; // TODO: make this strong typed

/**
 * Helpers of the wrapper. Do not worry - most compilers would be able to optimize this out
 * at about O2 level, which we surely will use.
 */
namespace {

template <typename C, typename... Ts>
struct WrapPass;

template <typename C, typename T, typename... Ts>
struct WrapPass<C, T, Ts...> {
    template <typename... Us>
    static void Call(System& system, std::shared_ptr<Us>... u) {
        for (auto item : system.GetElements(T::Type)) {
            WrapPass<C, Ts...>::Call(system, u..., std::dynamic_pointer_cast<T>(item));
        }
    }
};

template <typename C /* empty for T, Ts... */>
struct WrapPass<C> {
    template <typename... Us>
    static void Call(System& system, std::shared_ptr<Us>... u) {
        std::unordered_set<u64> S{{u->GetHash()...}};
        if (S.size() == sizeof...(u)) {
            C::Execute(system, u...);
        }
    }
};

} // namespace

/**
 * Wrapper template for theorems. One should use CRTP to extend this class.
 * (public class C : public Wrapper<C, ...>)
 *
 * A static function C::Execute is required to be present, arguments being
 * (system, Args...).
 */
template <typename C, typename... Args>
class Wrapper : public Transform {
public:
    void Execute(System& system) override {
        WrapPass<C, Args...>::Call(system);
    }
};

} // namespace Core

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

#include <symengine/basic.h>
#include "common/common_types.h"
#include "common/printer.h"

namespace Algebra {

/**
 * Checks whether the sign of the expression can be confirmed, assuming that all symbols are
 * positive.
 * @return 0 if unknown, 1 if positive, -1 if negative.
 */
s8 CheckSign(const SymEngine::RCP<const SymEngine::Basic>& expr);

/**
 * Checks whether an expression is acceptable, i.e. whether it CAN be positive.
 * For example, -y-z and -x-2 are not acceptable, while x-2 and x+y-1 are.
 */
bool IsAcceptable(const SymEngine::Expression& expr);

/**
 * Simplifies an equation, removing sqrt items.
 */
SymEngine::Expression SimplifyEquation(const SymEngine::Expression& expr);

/**
 * Converts an equation to strings (of different formats).
 * This may not be always equal to "X = 0". Instead it would put items with
 * symbols on the left side and items without symbols on the right side.
 */
Common::StringPack EquationToString(const SymEngine::Expression& expr);

/**
 * Registers the pretty name alias of a certain symbol.
 */
void RegisterSymbolPrettyName(const SymEngine::RCP<const SymEngine::Basic>& symbol,
                              const std::string& name);

} // namespace Algebra

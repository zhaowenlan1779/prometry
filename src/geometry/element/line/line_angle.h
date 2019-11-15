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

#include <utility>
#include "algebra/algebra.h"
#include "geometry/element/line/line.h"

namespace Core {

std::array<Algebra::Expression, 2> LineAngle(const std::shared_ptr<Line>& l1,
                                             const std::shared_ptr<Line>& l2);

Algebra::Expression LineAngle(const std::shared_ptr<Line>& l1, LineDirection d1,
                              const std::shared_ptr<Line>& l2, LineDirection d2);

} // namespace Core

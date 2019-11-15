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

#include "core/transform.h"
#include "geometry/element/line/line.h"

namespace Core {

class System;

class AnglesToPerpendicular : public Wrapper<AnglesToPerpendicular, Line, Line> {
public:
    explicit AnglesToPerpendicular();
    ~AnglesToPerpendicular() override;

    static void Execute(System& system, const std::shared_ptr<Line>& l1,
                        const std::shared_ptr<Line>& l2);
};

} // namespace Core

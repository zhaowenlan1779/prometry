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

#include "core/element.h"

namespace Core {

class Point;
class System;

enum class LineDirection {
    Normal,   ///< Starting from first child point
    Reversed, ///< Starting from last child point
};

class Line : public Element {
public:
    static ElementType Type;

    explicit Line(const std::string& name);
    ~Line() override;
    std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const override;
    ElementType GetType() const override;
    u64 GetHash() const override;
    LineDirection GetLineDirection(const std::shared_ptr<Point>& p1,
                                   const std::shared_ptr<Point>& p2) const;

    /**
     * Returns the line that connects the two points.
     * If such a line already exists, returns that line. Otherwise create a new one with the two
     * points added as children.
     */
    static std::pair<std::shared_ptr<Line>, LineDirection> Connect(
        System& system, const std::shared_ptr<Point>& p1, const std::shared_ptr<Point>& p2);

private:
    std::string name;
};

} // namespace Core

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

#ifndef PROSPEC_H
#define PROSPEC_H

// ProSpec is prometry's DSL for geometry problems specification.

#include <memory>
#include <string>
#include <tuple>
#include "core/system.h"
#include "geometry/conclusion/line_parallel.h"
#include "geometry/conclusion/line_perpendicular.h"
#include "geometry/conclusion/triangle_similar.h"
#include "geometry/construction/all_constructions.h"
#include "geometry/element/line/line.h"
#include "geometry/element/line/line_angle.h"
#include "geometry/element/line/line_segment.h"
#include "geometry/element/point.h"
#include "geometry/transform/all_transforms.h"

namespace Core::ProSpec {

// ====================================================== Helper macros

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a##__VA_ARGS__

// Number of arguments

#define PP_NARG(...) PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18,  \
                 _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34,   \
                 _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,   \
                 _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, N, ...)          \
    N
#define PP_RSEQ_N()                                                                                \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41,    \
        40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,    \
        18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// ====================================================== System macros

#define prospec_begin                                                                              \
    {                                                                                              \
        using namespace Core;                                                                      \
        System system;                                                                             \
        RegisterAllTransforms(system);                                                             \
        RegisterAllConstructions(system);

#define prospec_end }

// ====================================================== Common macros

#define str(...)                                                                                   \
    Common::StringPack {                                                                           \
        __VA_ARGS__                                                                                \
    }

// ====================================================== Element creation macros

// Point

#define POINT_1(p1) auto p1 = system.CreateElement<Point>("", #p1)
#define POINT_2(p1, p2)                                                                            \
    POINT_1(p1);                                                                                   \
    auto p2 = system.CreateElement<Point>("", #p2)
#define POINT_3(p1, p2, p3)                                                                        \
    POINT_2(p1, p2);                                                                               \
    auto p3 = system.CreateElement<Point>("", #p3)
#define POINT_4(p1, p2, p3, p4)                                                                    \
    POINT_3(p1, p2, p3);                                                                           \
    auto p4 = system.CreateElement<Point>("", #p4)
#define POINT_5(p1, p2, p3, p4, p5)                                                                \
    POINT_4(p1, p2, p3, p4);                                                                       \
    auto p5 = system.CreateElement<Point>("", #p5)
#define POINT_6(p1, p2, p3, p4, p5, p6)                                                            \
    POINT_5(p1, p2, p3, p4, p5);                                                                   \
    auto p6 = system.CreateElement<Point>("", #p6)
#define POINT_7(p1, p2, p3, p4, p5, p6, p7)                                                        \
    POINT_6(p1, p2, p3, p4, p5, p6);                                                               \
    auto p7 = system.CreateElement<Point>("", #p7)
#define POINT_8(p1, p2, p3, p4, p5, p6, p7, p8)                                                    \
    POINT_7(p1, p2, p3, p4, p5, p6, p7);                                                           \
    auto p8 = system.CreateElement<Point>("", #p8)
#define POINT_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)                                                \
    POINT_8(p1, p2, p3, p4, p5, p6, p7, p8);                                                       \
    auto p9 = system.CreateElement<Point>("", #p9)
#define POINT_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)                                          \
    POINT_9(p1, p2, p3, p4, p5, p6, p7, p8, p9);                                                   \
    auto p10 = system.CreateElement<Point>("", #p10)
#define POINT_11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)                                     \
    POINT_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);                                             \
    auto p11 = system.CreateElement<Point>("", #p11)
#define POINT_12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)                                \
    POINT_11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);                                        \
    auto p12 = system.CreateElement<Point>("", #p12)
#define POINT_13(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)                           \
    POINT_12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);                                   \
    auto p13 = system.CreateElement<Point>("", #p13)
#define POINT_14(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)                      \
    POINT_13(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);                              \
    auto p14 = system.CreateElement<Point>("", #p14)
#define POINT_15(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15)                 \
    POINT_14(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);                         \
    auto p15 = system.CreateElement<Point>("", #p15)
#define POINT_16(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16)            \
    POINT_15(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);                    \
    auto p16 = system.CreateElement<Point>("", #p16)
#define POINT_17(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17)       \
    POINT_16(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);               \
    auto p17 = system.CreateElement<Point>("", #p17)
#define POINT_18(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18)  \
    POINT_17(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17);          \
    auto p18 = system.CreateElement<Point>("", #p18)
#define POINT_19(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19)                                                                              \
    POINT_18(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18);     \
    auto p19 = system.CreateElement<Point>("", #p19)
#define POINT_20(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20)                                                                         \
    POINT_19(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,      \
             p19);                                                                                 \
    auto p20 = system.CreateElement<Point>("", #p20)
#define POINT_21(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21)                                                                    \
    POINT_20(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20);                                                                                 \
    auto p21 = system.CreateElement<Point>("", #p21)
#define POINT_22(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22)                                                               \
    POINT_21(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21);                                                                            \
    auto p22 = system.CreateElement<Point>("", #p22)
#define POINT_23(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23)                                                          \
    POINT_22(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22);                                                                       \
    auto p23 = system.CreateElement<Point>("", #p23)
#define POINT_24(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24)                                                     \
    POINT_23(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23);                                                                  \
    auto p24 = system.CreateElement<Point>("", #p24)
#define POINT_25(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25)                                                \
    POINT_24(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24);                                                             \
    auto p25 = system.CreateElement<Point>("", #p25)
#define POINT_26(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25, p26)                                           \
    POINT_25(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24, p25);                                                        \
    auto p26 = system.CreateElement<Point>("", #p26)
#define POINT_27(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25, p26, p27)                                      \
    POINT_26(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24, p25, p26);                                                   \
    auto p27 = system.CreateElement<Point>("", #p27)
#define POINT_28(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25, p26, p27, p28)                                 \
    POINT_27(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24, p25, p26, p27);                                              \
    auto p28 = system.CreateElement<Point>("", #p28)
#define POINT_29(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29)                            \
    POINT_28(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24, p25, p26, p27, p28);                                         \
    auto p29 = system.CreateElement<Point>("", #p29)
#define POINT_30(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18,  \
                 p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30)                       \
    POINT_29(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, \
             p20, p21, p22, p23, p24, p25, p26, p27, p28, p29);                                    \
    auto p30 = system.CreateElement<Point>("", #p30)

#define point(...) CAT(POINT_, PP_NARG(__VA_ARGS__))(__VA_ARGS__)

// Line

namespace detail {

template <typename... Args>
inline void AddLineChildren(const std::shared_ptr<Line>& l, Args&&... args);

template <typename T, typename... Args>
inline void AddLineChildren(const std::shared_ptr<Line>& l, T&& p, Args&&... args) {
    p->AddParent(l);
    AddLineChildren<Args...>(l, args...);
}

template <>
inline void AddLineChildren(const std::shared_ptr<Line>& l) {}

} // namespace detail

#define line_simple(name) auto name = system.CreateElement<Line>("", #name)

#define line(name, ...)                                                                            \
    line_simple(name);                                                                             \
    ProSpec::detail::AddLineChildren(name, ##__VA_ARGS__)

// ====================================================== Element properties macros

#define len(...) LineSegmentLength(__VA_ARGS__)
#define angle(...) LineAngle(__VA_ARGS__)
#define normal LineOrder::Normal
#define reversed LineOrder::Reversed

// ====================================================== Algebra convenience macros

#define pi SymEngine::Expression(SymEngine::pi)
#define frac(a, b) SymEngine::rational(a, b)

// ====================================================== Conclusion creation macros

namespace detail {

template <typename T, typename... Args>
inline void CreateConclusion(System& system, Args&&... args) {
    system.CreateConclusion<T>("hypothesis", {}, args...);
}

} // namespace detail

#define line_parallel(...) ProSpec::detail::CreateConclusion<LineParallel>(system, ##__VA_ARGS__)
#define line_perpendicular(...)                                                                    \
    ProSpec::detail::CreateConclusion<LinePerpendicular>(system, ##__VA_ARGS__)
#define triangle_similar(...)                                                                      \
    ProSpec::detail::CreateConclusion<TriangleSimilar>(system, ##__VA_ARGS__)

// ====================================================== Equation creation macros

#define equation(equ) system.Algebra().AddEquation(equ, "hypothesis")

// ====================================================== Execution macros

namespace detail {

inline std::shared_ptr<Common::ProofChainNode> ExecuteSingle(System& system,
                                                             const Conclusion& target) {
    auto conclusion = system.GetConclusion(target);
    return conclusion ? conclusion->GetProofNode() : nullptr;
}

inline std::shared_ptr<Common::ProofChainNode> ExecuteSingle(System& system,
                                                             const Algebra::Expression& target) {

    const auto& [ret, proof_node] = system.Algebra().CheckEquation(target);
    return ret ? proof_node : nullptr;
}

template <typename... Args>
inline std::vector<std::shared_ptr<Common::ProofChainNode>> ExecuteMultiple(System& system,
                                                                            Args&&... args);

template <typename T, typename... Args>
inline std::vector<std::shared_ptr<Common::ProofChainNode>> ExecuteMultiple(System& system,
                                                                            T&& target,
                                                                            Args&&... args) {
    auto proof_node = ExecuteSingle(system, target);
    if (!proof_node) {
        return {};
    }
    auto list = ExecuteMultiple<Args...>(system, args...);
    list.emplace_back(proof_node);
    return list;
}

template <>
inline std::vector<std::shared_ptr<Common::ProofChainNode>> ExecuteMultiple(System& system) {
    return {};
}

template <typename... Args>
inline std::string Execute(System& system, Common::StringPack statement, std::string transform,
                           Args&&... args) {

    return system.Execute([&](System& system) -> std::shared_ptr<Common::ProofChainNode> {
        const auto& list = ExecuteMultiple(system, args...);

        if (list.empty())
            return nullptr;
        if (list.size() == 1)
            return list[0];

        // Create a new proof node
        const auto& proof_node = std::make_shared<Common::ProofChainNode>();
        proof_node->statement = std::move(statement);
        proof_node->transform = std::move(transform);
        for (const auto& iter : list) {
            proof_node->reasons.emplace_back(iter);
        }

        return proof_node;
    });
}

} // namespace detail

#define execute_single(target) ProSpec::detail::Execute(system, {}, {}, target)
#define execute_multiple(statement, transform, ...)                                                \
    ProSpec::detail::Execute(system, statement, transform, __VA_ARGS__)

} // namespace Core::ProSpec

#else
// We used macro guard instead of #pragma once, just for this error message.
#error prospec.h was included multiple times, please include it once only.
#endif

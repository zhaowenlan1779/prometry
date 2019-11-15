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

#include <cstdlib>
#include <iostream>

#ifdef _MSC_VER

extern "C" {
__declspec(dllimport) void __stdcall DebugBreak(void);
}
#define CRASH() DebugBreak()

#else // _MSC_VER

#ifdef ARCHITECTURE_x86_64
#define CRASH() __asm__ __volatile__("int $3")
#else
#define CRASH() exit(1)
#endif

#endif // _MSC_VER

// This is a helper to force no inline.
template <typename Fn>
#if defined(_MSC_VER)
[[ noinline, noreturn ]]
#elif defined(__GNUC__)
[[ noinline, noreturn, gnu::cold ]]
#endif
    static void
    assert_wrapper(const Fn& fn) {
    fn();
    CRASH();
    exit(1);
}

#define ASSERT(_a_)                                                                                \
    do                                                                                             \
        if (!(_a_)) {                                                                              \
            assert_wrapper([] { std::cerr << "Assertion Failed!\n"; });                            \
        }                                                                                          \
    while (0)

#define ASSERT_MSG(_a_, ...)                                                                       \
    do                                                                                             \
        if (!(_a_)) {                                                                              \
            assert_wrapper([&] { std::cerr << "Assertion Failed!\n" __VA_ARGS__ "\n"; });          \
        }                                                                                          \
    while (0)

#define UNREACHABLE() ASSERT_MSG(false, "Unreachable code!")
#define UNREACHABLE_MSG(...) ASSERT_MSG(false, __VA_ARGS__)

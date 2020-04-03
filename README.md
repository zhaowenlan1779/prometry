Prometry
=========
Geometry mechanical proving using plain search algorithms. This is more or less some sort of school project that is very slow and unfinished

Licensed under MIT

## Building

### Cloning

Clone with `--recursive`, or call `git submodule update --init --recursive` after you clone the repo.

### Dependencies

This project uses CMake and C++17, use a conforming compiler. This project relies on the [SymEngine](https://github.com/symengine/symengine) algebra library. 

#### MSVC

Only Visual Studio 2017/2019 is supported as we need experimental preprocessor.

You can install SymEngine with conda. You will probably need to configure CMake to point to your install.

#### Mingw / UNIX-Like

You must build and install the SymEngine library before building this project. Attached is a simple command snippet for building and installing SymEngine on MSYS2 Mingw64 (ensure that a good toolchain and ninja-build is present. you'll also need libgmp).

```bash
git clone https://github.com/symengine/symengine.git
cd symengine
cmake -DCMAKE_INSTALL_PREFIX:PATH="/mingw64" -GNinja .
ninja
ninja install
```

## Testing

A `tests` project is available, which consists of multiple unit and integrated tests.

## Usage

Currently, prometry does not have a frontend, but you can already use it in the code.

prometry uses a DSL made by C macros and C++ template metaprogramming called ProSpec. Include the file `geometry/prospec.h` to use it. You can refer to the tests on how to use the DSL.

Example (taken from `tests/integrated/pythagorean.cpp`):
```cpp
    prospec_begin;

    point(A, B, C, D);
    line(l1, A, C);
    line(l2, B, C, D);

    line_perpendicular(l1, l2);

    equation(len(A, C) - 1);
    equation(len(B, C) - 3);
    equation(len(A, D) - len(D, B));

    const auto proof = execute_single(len(A, D) - frac(5, 3));
    std::cout << "Proof: " << proof << std::endl;
    REQUIRE(!proof.empty());

    prospec_end;
```

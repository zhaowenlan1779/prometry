Prometry
=========
Geometry machine proof

## Building

### Cloning

This project uses git submodule to manage externals. Do not forget to call `git submodule update`, or clone this repo with `--recursive`.

You will be prompted by an error if CMake detects that your clone is incomplete due to missing submodules.

### Dependencies

This project uses the CMake building system. C++17 is required, so you will need a recent enough compiler, such as g++ 7 or above.

This project relies on the [SymEngine](https://github.com/symengine/symengine) algebra library. You must build and install the SymEngine library before building this project. Attached is a simple command snippet for building and installing SymEngine on MSYS2 Mingw64 (ensure that a good toolchain and ninja-build is present. you'll also need libgmp).

```bash
git clone https://github.com/symengine/symengine.git
cd symengine
cmake -DCMAKE_INSTALL_PREFIX:PATH="/mingw64" -GNinja .
ninja
ninja install
```

## Testing

A `tests` project is available, which consists of multiple unit and integrated tests. You can use CMake's testing system (CTest) or just build the project manually.

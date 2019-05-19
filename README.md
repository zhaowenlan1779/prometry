Prometry
=========
Geometry machine proof

## Building
This project uses git submodule to manage externals. Do not forget to call `git submodule update`, or clone this repo with `--recursive`.

This project uses the CMake building system. C++17 is required, so you will need a recent enough version of g++ (7 or above).

## Testing
A `tests` project is available, which consists of multiple unit and integrated tests. You can use CMake's testing system (CTest) or build the project manually.

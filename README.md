Prometry
=========
Geometry machine proof

## Building

### Cloning

Clone with `--recursive`, or call `git submodule update --init --recursive` after you clone the repo.

### Dependencies

This project uses CMake, and employs C++17 features. (Though it shouldn't be hard to move to C++14 or C++11)

This project relies on the [SymEngine](https://github.com/symengine/symengine) algebra library. You must build and install the SymEngine library before building this project. Attached is a simple command snippet for building and installing SymEngine on MSYS2 Mingw64 (ensure that a good toolchain and ninja-build is present. you'll also need libgmp).

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

Refer to the tests for examples on using this (not-really-a)library. Basically:

* Always create a `System` and pass it around before doing anything. It'll manage (own) all the elements, conclusions as well as sub-procedures called transforms or constructions.
* Add in the transforms and constructions you need, or just import everything with the all_transforms and all_constructions helper.
* Create the elements.
* Add in parent-children relationship of the elements with the `AddParent` method.
* Create conclusions, and add in algebra relations if any.
* Execute the system with `system.Execute(callback)`.
    * The `callback` should be a function that takes a `System&` and returns a pointer to `Common::ProofChainNode` when the target is already reached and `nullptr` otherwise.
    * If you want to execute the system until it stops, just say `system.Execute([](System&) {return nullptr;})`.

Example (taken from `tests/integrated/pythagorean.cpp`):
```cpp
    System system;
    RegisterAllTransforms(system);
    RegisterAllConstructions(system);
    auto a = system.CreateElement<Point>("", "A");
    auto b = system.CreateElement<Point>("", "B");
    auto c = system.CreateElement<Point>("", "C");
    auto d = system.CreateElement<Point>("", "D");
    auto l1 = system.CreateElement<Line>("", "l1");
    auto l2 = system.CreateElement<Line>("", "l2");
    system.CreateConclusion<LinePrependicular>("", {}, l1, l2);

    a->AddParent(l1);
    b->AddParent(l2);
    c->AddParent(l1);
    c->AddParent(l2);
    d->AddParent(l2);

    system.Algebra().AddEquation(LineSegmentLength(a, c) - 1);
    system.Algebra().AddEquation(LineSegmentLength(b, c) - 3);
    system.Algebra().AddEquation(LineSegmentLength(a, d) - LineSegmentLength(d, b));

    const auto proof = system.Execute([&a, &d](System& system) {
        const auto& [ret, proof_node] = system.Algebra().CheckEquation(
            LineSegmentLength(a, d) - Algebra::Expression(5) / Algebra::Expression(3));
        return ret ? proof_node : nullptr;
    });

    std::cout << "Proof: " << proof << std::endl;
```

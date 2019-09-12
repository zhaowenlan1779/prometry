// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <unordered_set>
#include "common/common_types.h"
#include "core/system.h"

namespace Core {

/**
 * Virtual interface for transforms.
 *
 * Transforms are generalized templates that consist of axioms, thereoms and common models,
 * which can be used in the proof. (common models will get expanded)
 */
class Transform {
public:
    virtual ~Transform() = default;
    virtual void Execute(System& system) = 0;
};

/**
 * Virtual interface for constructions.
 *
 * Constructions are generalized templates used to construct additional elements besides those
 * already present.
 */
using Construction = Transform; // TODO: make this strong typed

/**
 * Map that stores "the count of elements of a certain type when last executed".
 * When executed again, the transform will use this value to optimize out unnecessary queries.
 */
using TypeMap = std::unordered_map<ElementType, std::size_t>;

/**
 * Helpers of the wrapper. Do not worry - most compilers would be able to optimize this out
 * at about O2 level, which we surely will use.
 */
namespace {

template <typename C, typename... Ts>
struct WrapPass;

template <typename C, typename T, typename... Ts>
struct WrapPass<C, T, Ts...> {
    template <typename... Us>
    static void Call(System& system, const TypeMap& map, bool is_old,
                     const std::shared_ptr<Us>&... u) {

        const auto& elements = system.GetElements(T::Type);
        for (std::size_t i = 0; i < elements.size(); ++i) {
            WrapPass<C, Ts...>::Call(system, map,
                                     is_old && i <= (map.count(T::Type) ? map.at(T::Type) : 0),
                                     u..., std::dynamic_pointer_cast<T>(elements[i]));
        }
    }
};

template <typename C, typename T /* empty for Ts... */>
struct WrapPass<C, T> {
    template <typename... Us>
    static void Call(System& system, const TypeMap& map, bool is_old,
                     const std::shared_ptr<Us>&... u) {

        const auto& elements = system.GetElements(T::Type);
        for (std::size_t i = (is_old && map.count(T::Type) ? map.at(T::Type) : 0);
             i < elements.size(); ++i) {
            WrapPass<C>::Call(system, map, false, u..., std::dynamic_pointer_cast<T>(elements[i]));
        }
    }
};

template <typename C /* empty for T, Ts... */>
struct WrapPass<C> {
    template <typename... Us>
    static void Call(System& system, const TypeMap& map, bool is_old,
                     const std::shared_ptr<Us>&... u) {

        std::unordered_set<u64> S{{u->GetHash()...}};
        if (S.size() == sizeof...(u)) {
            C::Execute(system, u...);
        }
    }
};

} // namespace

/**
 * A similar wrapper just to update the TypeMap.
 * TODO: Why these have to be structs? (overload resolution is strange here)
 */
namespace {

template <typename... Args>
struct TypeMapUpdateWrapper;

template <typename Arg, typename... Args>
struct TypeMapUpdateWrapper<Arg, Args...> {
    static void UpdateTypeMap(TypeMap& map, System& system) {
        map[Arg::Type] = system.GetElements(Arg::Type).size();
        TypeMapUpdateWrapper<Args...>::UpdateTypeMap(map, system);
    }
};

template <>
struct TypeMapUpdateWrapper<> {
    static void UpdateTypeMap(TypeMap& map, System& system) {}
};

} // namespace

/**
 * Wrapper template for theorems. One should use CRTP to extend this class.
 * (public class C : public Wrapper<C, ...>)
 *
 * A static function C::Execute is required to be present, arguments being
 * (system, const std::shared_ptr<Args>&...).
 */
template <typename C, typename... Args>
class Wrapper : public Transform {
public:
    void Execute(System& system) override {
        WrapPass<C, Args...>::Call(system, map, true);
        TypeMapUpdateWrapper<Args...>::UpdateTypeMap(map, system);
    }

private:
    TypeMap map;
};

} // namespace Core

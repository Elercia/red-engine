#pragma once

#include "RedEngine/Math/Hash.hpp"

#include <string_view>
#include <tuple>

namespace red
{
template <bool...>
struct bool_pack;
template <bool... bs>
using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

template <std::size_t I = 0, typename FuncT, typename... Tp>
inline constexpr typename std::enable_if<I == sizeof...(Tp), void>::type for_each(
    std::tuple<Tp...>&, FuncT)  // Unused arguments are given no names.
{
}

template <std::size_t I = 0, typename FuncT, typename... Tp>
    inline constexpr typename std::enable_if < I<sizeof...(Tp), void>::type for_each(std::tuple<Tp...>& t, FuncT f)
{
    f(std::get<I>(t));
    for_each<I + 1, FuncT, Tp...>(t, f);
}

using TypeTraitsId = uint32;

struct TypeTraits
{
    std::string_view name;
    TypeTraitsId typeId;

    bool operator==(const TypeTraits& other) const
    {
        return other.typeId == typeId;
    }

    bool operator!=(const TypeTraits& other) const
    {
        return other.typeId != typeId;
    }
};

constexpr TypeTraits EmptyTypeTraits{"invalid", (uint32) -1};

#if defined(_MSC_VER) && !defined(__clang__)
#define RED_FUNCNAME              __FUNCSIG__
#define RED_FUNCNAME_START        "red::TypeInfo<"
#define RED_FUNCNAME_END          ">(void)"
#define RED_FUNCNAME_STRUCT_START "struct "
#define RED_FUNCNAME_CLASS_START  "class "
#elif defined(__clang__)
#define RED_FUNCNAME              __PRETTY_FUNCTION__
#define RED_FUNCNAME_START        "red::TypeInfo() [T ="
#define RED_FUNCNAME_END          "]"
#define RED_FUNCNAME_STRUCT_START ""
#define RED_FUNCNAME_CLASS_START  ""
#elif defined(__GNUC__)
#define RED_FUNCNAME              __PRETTY_FUNCTION__
#define RED_FUNCNAME_START        "red::TypeInfo() [with T = "
#define RED_FUNCNAME_END          "]"
#define RED_FUNCNAME_STRUCT_START "struct "
#define RED_FUNCNAME_CLASS_START  "class "
#endif

#define RED_TYPE_INFO(var) red::TypeInfo<decltype(var)>()

template <typename T>
constexpr TypeTraits TypeInfo();

inline TypeTraits GetTypeInfoFromTypeName(std::string_view name);
}  // namespace red

#include "inl/TypesInfo.inl"
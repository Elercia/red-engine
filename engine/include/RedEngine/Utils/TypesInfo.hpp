#pragma once

#include "RedEngine/Math/Hash.hpp"

#include <string_view>

namespace red
{
struct TypeTraits
{
    std::string_view name;
    uint32 typeId;
};

#ifdef _MSC_VER
#define RED_FUNCNAME __FUNCSIG__
#define RED_FUNCNAME_START "red::TypeInfo<"
#define RED_FUNCNAME_END ">(void)"
#define RED_FUNCNAME_STRUCT_START "struct "
#define RED_FUNCNAME_CLASS_START "class "
#elif __GNUC__
#define RED_FUNCNAME __PRETTY_FUNCTION__
#define RED_FUNCNAME_START "red::TypeInfo() [with T = "
#define RED_FUNCNAME_END "]"
#define RED_FUNCNAME_STRUCT_START "struct "
#define RED_FUNCNAME_CLASS_START "class "
#endif

#define RED_TYPE_INFO(var) red::TypeInfo<decltype(var)>()

template <typename T>
constexpr TypeTraits TypeInfo();
}  // namespace red

#include "inl/TypesInfo.inl"
#include <string_view>

namespace red
{
struct TypeTraits
{
    std::string_view name;
    const int typeId;
};

#ifdef _MSC_VER
#define RED_FUNCNAME "red::TypeInfo<NoInfo>(void)"
#define RED_FUNCNAME_START "red::TypeInfo<"
#define RED_FUNCNAME_END ">(void)"
#elif __GCC__
#define RED_FUNCNAME __PRETTY_FUNCTION__
#endif

template <typename T>
constexpr TypeTraits TypeInfo();
}  // namespace red

#include "inl/TypesInfo.inl"
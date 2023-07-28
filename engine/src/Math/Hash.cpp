#include "RedEngine/Math/Hash.hpp"

#include "RedEngine/Math/MathModule.hpp"

#include "RedEngine/Utils/Types.hpp"

namespace red
{
template <>
uint64 Hash(const int& value)
{
    return (uint64)value;
}

// FIXME Implement these
template <>
uint64 Hash(const double& /*value*/)
{
    return 0;
}

template <>
uint64 Hash(const float& /*value*/)
{
    return 0;
}

template <>
uint64 Hash(const uint8& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const uint16& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const uint32& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const uint64& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const int8& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const int16& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const int64& value)
{
    return (uint64)value;
}

template <>
uint64 Hash(const String& value)
{
    return fnv1a32(value);
}

}  // namespace red
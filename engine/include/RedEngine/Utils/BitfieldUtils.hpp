#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
template <typename T, typename O>
inline void SetBit(T& value, O bit)
{
    value |= bit;
}

template <typename T, typename O>
inline bool HasBit(const T& value, O bit)
{
    return (value & bit) != 0;
}
}  // namespace red
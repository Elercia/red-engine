#pragma once

#include <RedEngine/Utils/Types.hpp>

#include <string_view>

namespace red
{
constexpr uint32 fnv1a32(const std::string_view& s, sizet count);
constexpr uint32 fnv1a32(const std::string_view& s);
}  // namespace red

#include "inl/Hash.inl"
#pragma once

#include <RedEngine/Utils/Types.hpp>

#include <string_view>

namespace red
{
constexpr uint32 fnv1a32(const std::string_view& s, sizet count);
constexpr uint32 fnv1a32(const std::string_view& s);

constexpr uint32 wfnv1a32(const std::wstring_view& s, sizet count);
constexpr uint32 wfnv1a32(const std::wstring_view& s);

template <typename T>
uint64 Hash(const T& value);

template <>
uint64 Hash(const int& value);
template <>
uint64 Hash(const double& value);
template <>
uint64 Hash(const float& value);
template<>
uint64 Hash(const uint8& value);
template<>
uint64 Hash(const uint16& value);
template<>
uint64 Hash(const uint32& value);
template<>
uint64 Hash(const uint64& value);
template<>
uint64 Hash(const int8& value);
template<>
uint64 Hash(const int16& value);
template<>
uint64 Hash(const int64& value);

// Common object hahing
template<>
uint64 Hash(const std::string& value);

}  // namespace red

#include "inl/Hash.inl"
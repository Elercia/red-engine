#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <string>

namespace red
{
template <typename T>
std::string Serialize(const T& value);
template <typename T>
bool Deserialize(T& value, const std::string& str);
}  // namespace red

#include "inl/SerializationFunction.inl"

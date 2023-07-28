#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Utils/Types.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
template <typename T>
String Serialize(const T& value);
template <typename T>
bool Deserialize(T& value, const String& str);
}  // namespace red

#include "inl/SerializationFunction.inl"

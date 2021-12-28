#pragma once 

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"

#include <string>

namespace red
{
template <>
std::string Serialize(const Vector2& value);
template <>
bool Deserialize(Vector2& value, const std::string& str);
}  // namespace red
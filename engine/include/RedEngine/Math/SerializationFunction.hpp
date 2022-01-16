#pragma once

#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <string>

namespace red
{
template <>
std::string Serialize(const Vector2& value);
template <>
bool Deserialize(Vector2& value, const std::string& str);

template <>
std::string Serialize(const Vector2i& value);
template <>
bool Deserialize(Vector2i& value, const std::string& str);

template <>
std::string Serialize(const Vector3& value);
template <>
bool Deserialize(Vector3& value, const std::string& str);

template <>
std::string Serialize(const Vector3i& value);
template <>
bool Deserialize(Vector3i& value, const std::string& str);

template <>
std::string Serialize(const Vector4& value);
template <>
bool Deserialize(Vector4& value, const std::string& str);

template <>
std::string Serialize(const Vector4i& value);
template <>
bool Deserialize(Vector4i& value, const std::string& str);
}  // namespace red
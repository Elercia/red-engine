#pragma once

#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Math/Vector.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
template <>
String Serialize(const Vector2& value);
template <>
bool Deserialize(Vector2& value, const String& str);

template <>
String Serialize(const Vector2i& value);
template <>
bool Deserialize(Vector2i& value, const String& str);

template <>
String Serialize(const Vector3& value);
template <>
bool Deserialize(Vector3& value, const String& str);

template <>
String Serialize(const Vector3i& value);
template <>
bool Deserialize(Vector3i& value, const String& str);

template <>
String Serialize(const Vector4& value);
template <>
bool Deserialize(Vector4& value, const String& str);

template <>
String Serialize(const Vector4i& value);
template <>
bool Deserialize(Vector4i& value, const String& str);
}  // namespace red
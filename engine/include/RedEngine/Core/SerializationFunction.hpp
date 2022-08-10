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

/*template <>
template <typename T>
std::string Serialize(const Array<T>& value);

template <>
template <typename T>
bool Deserialize(Array<T>& value, const std::string& str);*/

template <>
std::string Serialize(const bool& value);
template <>
bool Deserialize(bool& value, const std::string& str);

template <>
std::string Serialize(const double& value);
template <>
bool Deserialize(double& value, const std::string& str);

template <>
std::string Serialize(const float& value);
template <>
bool Deserialize(float& value, const std::string& str);

template <>
std::string Serialize(const int8& value);
template <>
bool Deserialize(int8& value, const std::string& str);

template <>
std::string Serialize(const int16& value);
template <>
bool Deserialize(int16& value, const std::string& str);

template <>
std::string Serialize(const int32& value);
template <>
bool Deserialize(int32& value, const std::string& str);

template <>
std::string Serialize(const int64& value);
template <>
bool Deserialize(int64& value, const std::string& str);

template <>
std::string Serialize(const uint8& value);
template <>
bool Deserialize(uint8& value, const std::string& str);

template <>
std::string Serialize(const uint16& value);
template <>
bool Deserialize(uint16& value, const std::string& str);

template <>
std::string Serialize(const uint32& value);
template <>
bool Deserialize(uint32& value, const std::string& str);

template <>
std::string Serialize(const uint64& value);
template <>
bool Deserialize(uint64& value, const std::string& str);

template <>
std::string Serialize(const std::string& value);
template <>
bool Deserialize(std::string& value, const std::string& str);

}  // namespace red

#include "inl/SerializationFunction.inl"

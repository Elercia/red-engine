#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <string>

namespace red
{
template <typename T>
std::string Serialize(const Array<T>& value);
template <typename T>
bool Deserialize(Array<T>& value, const std::string& str);

std::string Serialize(const bool& value);
bool Deserialize(bool& value, const std::string& str);

std::string Serialize(const double& value);
bool Deserialize(double& value, const std::string& str);

std::string Serialize(const float& value);
bool Deserialize(float& value, const std::string& str);

std::string Serialize(const int8& value);
bool Deserialize(int8& value, const std::string& str);

std::string Serialize(const int16& value);
bool Deserialize(int16& value, const std::string& str);

std::string Serialize(const int32& value);
bool Deserialize(int32& value, const std::string& str);

std::string Serialize(const int64& value);
bool Deserialize(int64& value, const std::string& str);

std::string Serialize(const uint8& value);
bool Deserialize(uint8& value, const std::string& str);

std::string Serialize(const uint16& value);
bool Deserialize(uint16& value, const std::string& str);

std::string Serialize(const uint32& value);
bool Deserialize(uint32& value, const std::string& str);

std::string Serialize(const uint64& value);
bool Deserialize(uint64& value, const std::string& str);

std::string Serialize(const std::string& value);
bool Deserialize(std::string& value, const std::string& str);

}  // namespace red

#include "inl/SerializationFunction.inl"
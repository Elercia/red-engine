#include "RedEngine/Core/SerializationFunction.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Utils/StringUtils.hpp"

using namespace red::utils;  // StringReader

namespace red
{
template <>
String Serialize(const bool& value)
{
    return value ? "1" : "0";
}

template <>
bool Deserialize(bool& value, const String& str)
{
    value = false;

    if (str == "1" || str == "true")
        value = true;

    return true;
}

template <>
String Serialize(const double& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(double& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(StringParser::ReadDouble(&it, end, value));

    return true;
}

template <>
String Serialize(const float& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(float& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(StringParser::ReadFloat(&it, end, value));

    return true;
}

template <>
String Serialize(const int8& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(int8& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    int intValue = 0;
    CheckReturn(StringParser::ReadInt(&it, end, intValue));
    value = (int8) intValue;

    return true;
}

template <>
String Serialize(const int16& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(int16& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    int intValue = 0;
    CheckReturn(StringParser::ReadInt(&it, end, intValue));
    value = (int16) intValue;

    return true;
}

template <>
String Serialize(const int32& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(int32& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    int intValue = 0;
    CheckReturn(StringParser::ReadInt(&it, end, intValue));
    value = (int32) intValue;

    return true;
}

template <>
String Serialize(const int64& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(int64& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(StringParser::ReadLong(&it, end, value));

    return true;
}

template <>
String Serialize(const uint8& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(uint8& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    uint32 intValue = 0;
    CheckReturn(StringParser::ReadUnsignedInt(&it, end, intValue));
    value = (uint8) intValue;

    return true;
}

template <>
String Serialize(const uint16& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(uint16& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    uint32 intValue = 0;
    CheckReturn(StringParser::ReadUnsignedInt(&it, end, intValue));
    value = (uint16) intValue;

    return true;
}

template <>
String Serialize(const uint32& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(uint32& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    uint32 intValue = 0;
    CheckReturn(StringParser::ReadUnsignedInt(&it, end, intValue));
    value = (uint32) intValue;

    return true;
}

template <>
String Serialize(const uint64& value)
{
    return std::to_string(value);
}

template <>
bool Deserialize(uint64& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(StringParser::ReadUnsignedLong(&it, end, value));

    return true;
}

template <>
String Serialize(const String& value)
{
    return value;
}

template <>
bool Deserialize(String& value, const String& str)
{
    value = str;
    return true;
}

}  // namespace red
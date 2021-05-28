
#include "RedEngine/Core/SerializationFunction.hpp"

namespace red
{
std::string Serialize(const bool& value)
{
    return value ? "1" : "0";
}
bool Deserialize(bool& value, const std::string& str)
{
    value = false;

    if (str == "1")
        value = true;

    return true;
}

std::string Serialize(const double& value)
{
    return std::to_string(value);
}
bool Deserialize(double& value, const std::string& str)
{
    char* endptr = nullptr;
    value = strtod(str.c_str(), &endptr);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const float& value)
{
    return std::to_string(value);
}
bool Deserialize(float& value, const std::string& str)
{
    char* endptr = nullptr;
    value = (float)strtod(str.c_str(), &endptr);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const int8& value)
{
    return std::to_string(value);
}
bool Deserialize(int8& value, const std::string& str)
{
    char* endptr = nullptr;
    value = (int8) strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const int16& value)
{
    return std::to_string(value);
}
bool Deserialize(int16& value, const std::string& str)
{
    char* endptr = nullptr;
    value = (int16) strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const int32& value)
{
    return std::to_string(value);
}
bool Deserialize(int32& value, const std::string& str)
{
    char* endptr = nullptr;
    value = strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const int64& value)
{
    return std::to_string(value);
}
bool Deserialize(int64& value, const std::string& str)
{
    char* endptr = nullptr;
    value = strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const uint8& value)
{
    return std::to_string(value);
}
bool Deserialize(uint8& value, const std::string& str)
{
    char* endptr = nullptr;
    value = (uint8) strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const uint16& value)
{
    return std::to_string(value);
}
bool Deserialize(uint16& value, const std::string& str)
{
    char* endptr = nullptr;
    value = (uint16) strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const uint32& value)
{
    return std::to_string(value);
}
bool Deserialize(uint32& value, const std::string& str)
{
    char* endptr = nullptr;
    value = strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const uint64& value)
{
    return std::to_string(value);
}
bool Deserialize(uint64& value, const std::string& str)
{
    char* endptr = nullptr;
    value = strtol(str.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

std::string Serialize(const std::string& value)
{
    return value;
}
bool Deserialize(std::string& value, const std::string& str)
{
    value = str;
    return true;
}

}  // namespace red
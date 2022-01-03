#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <sstream>

#define RED_NEW_CONFIG_TYPE_SERIALIZATOR(TYPE) \
    inline std::string red_serialize_configuration_type(const TYPE& typeValue)

#define RED_NEW_CONFIG_TYPE_DESERIALIZATOR(TYPE) \
    inline void red_deserialize_configuration_type(const std::string& stringValue, TYPE& typeValue)

namespace red
{
RED_NEW_CONFIG_TYPE_SERIALIZATOR(int)
{
    std::stringstream ss;
    ss << typeValue;
    std::string s;
    ss >> s;

    return s;
}
RED_NEW_CONFIG_TYPE_DESERIALIZATOR(int)
{
    char* p;
    long converted = std::strtol(stringValue.c_str(), &p, 10);
    if (*p != '\0')
    {
        // conversion failed because the input wasn't a number
        RED_LOG_WARNING("Deserializing value {} is not a int", stringValue);

        typeValue = 0;
        return;
    }

    typeValue = converted;
}

RED_NEW_CONFIG_TYPE_SERIALIZATOR(double)
{
    std::stringstream ss;
    ss << typeValue;
    std::string s;
    ss >> s;

    return s;
}
RED_NEW_CONFIG_TYPE_DESERIALIZATOR(double)
{
    char* p;
    double converted = std::strtod(stringValue.c_str(), &p);
    if (*p != '\0')
    {
        // conversion failed because the input wasn't a number
        RED_LOG_WARNING("Deserializing value {} is not a double", stringValue);

        typeValue = 0;
        return;
    }

    typeValue = converted;
}

RED_NEW_CONFIG_TYPE_SERIALIZATOR(bool)
{
    if (typeValue)
        return "true";

    return "false";
}

RED_NEW_CONFIG_TYPE_DESERIALIZATOR(bool)
{
    if (stringValue == "true")
    {
        typeValue = true;
        return;
    }

    if (stringValue == "false")
    {
        typeValue = false;
        return;
    }

    RED_LOG_WARNING("Deserializing value {} is not a bool", stringValue);
    typeValue = false;
}

RED_NEW_CONFIG_TYPE_SERIALIZATOR(std::string)
{
    return typeValue;
}
RED_NEW_CONFIG_TYPE_DESERIALIZATOR(std::string)
{
    typeValue = stringValue;
}

template <typename T>
class has_serialization_overload
{
    template <typename U>
    static constexpr std::false_type test(...)
    {
        return {};
    }

    template <typename U>
    static constexpr auto test(U* u) ->
        typename std::is_same<std::string, decltype(red_serialize_configuration_type(*u))>::type
    {
        return {};
    }

public:
    static constexpr bool value = test<T>(nullptr);
};

template <typename T>
class has_deserialization_overload
{
    template <typename U>
    static constexpr std::false_type test(...)
    {
        return {};
    }

    template <typename U>
    static constexpr auto test(U* u) ->
        typename std::is_same<void, decltype(red_deserialize_configuration_type(std::string(), *u))>::type
    {
        return {};
    }

public:
    static constexpr bool value = test<T>(nullptr);
};

}  // namespace red

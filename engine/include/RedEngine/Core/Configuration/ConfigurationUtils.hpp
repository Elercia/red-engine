#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <string>

namespace red
{
class CVarValue;

class ConfigurationUtils
{
public:
    static bool IsBool(const std::string& value, bool& outValue);
    static bool IsInt(const std::string& value, int& outValue);
    static bool IsDouble(const std::string& value, double& outValue);

    ConfigurationUtils() = delete;
    ~ConfigurationUtils() = delete;

    static std::string GetLongName(const std::string& category, const std::string& key);
    static std::string GetLongName(const CVarValue* cVar);
};
}  // namespace red

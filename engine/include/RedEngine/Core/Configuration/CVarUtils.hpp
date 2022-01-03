#pragma once

#include <string>

namespace red
{
class CVarValue;

class CVarUtils
{
public:
    static bool IsBool(const std::string& value, bool& outValue);
    static bool IsInt(const std::string& value, int& outValue);
    static bool IsDouble(const std::string& value, double& outValue);

    static std::string GetLongName(const std::string& category, const std::string& key);
    static std::string GetLongName(const CVarValue* cVar);

private:
    CVarUtils() = delete;
    ~CVarUtils() = delete;
};
}  // namespace red

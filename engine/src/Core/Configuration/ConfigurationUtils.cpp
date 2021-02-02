#include "RedEngine/Core/Configuration/ConfigurationUtils.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"

#include <cstdlib>

namespace red
{
bool ConfigurationUtils::IsInt(const std::string& value, int& outValue)
{
    char* p;
    long converted = std::strtol(value.c_str(), &p, 10);
    if (*p != '\0')
    {
        // conversion failed because the input wasn't a number
        return false;
    }

    outValue = converted;
    return true;
}

bool ConfigurationUtils::IsDouble(const std::string& value, double& outValue)
{
    char* p;
    double converted = std::strtod(value.c_str(), &p);
    if (*p != '\0')
    {
        // conversion failed because the input wasn't a number
        return false;
    }

    outValue = converted;
    return true;
}

std::string ConfigurationUtils::GetLongName(const std::string& category, const std::string& key)
{
    return category + "_" + key;
}

std::string ConfigurationUtils::GetLongName(const CVarValue* cVar)
{
    return GetLongName(cVar->GetCategory(), cVar->GetName());
}
}  // namespace red

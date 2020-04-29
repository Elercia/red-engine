#include <RedEngine/Core/Configuration/ConfigurationUtils.hpp>
#include <RedEngine/Core/Configuration/CVar.hpp>
#include <cstdlib>

bool red::ConfigurationUtils::IsBool(const std::string& value, bool& outValue)
{
    if (value == "true")
    {
        outValue = true;
        return true;
    }

    if (value == "false")
    {
        outValue = false;
        return true;
    }

    return false;
}
bool red::ConfigurationUtils::IsInt(const std::string& value, int& outValue)
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

bool red::ConfigurationUtils::IsDouble(const std::string& value, double& outValue)
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

std::string red::ConfigurationUtils::GetLongName(const std::string& category,
                                                 const std::string& key)
{
    return category + "_" + key;
}

std::string red::ConfigurationUtils::GetLongName(const red::ICVarValue* cVar)
{
    return GetLongName(cVar->GetCategory(), cVar->GetName());
}

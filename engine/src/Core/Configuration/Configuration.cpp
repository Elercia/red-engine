
#include <RedEngine/Core/Configuration/IniReader.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <RedEngine/Core/Configuration/ConfigurationUtils.hpp>
#include <utility>
#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"

namespace red
{
Configuration::Configuration() {}

Configuration::~Configuration()
{
    for (auto& pair : m_configVariable)
    {
        delete pair.second;
    }
}

void Configuration::ParseCommandLine(int argc, char** argv) {}

Configuration& Configuration::GetInstance()
{
    static Configuration instance;
    return instance;
}

void Configuration::LoadConfigFile(std::filesystem::path path)
{
    auto iniCatKeyValues = utils::IniReader::ReadFromFile(std::move(path));

    for (auto& iniCatKeyValue : iniCatKeyValues)
    {
        auto& cat = std::get<0>(iniCatKeyValue);
        auto& key = std::get<1>(iniCatKeyValue);
        auto& value = std::get<2>(iniCatKeyValue);

        auto foundVar = m_configVariable.find(ConfigurationUtils::GetLongName(cat, key));
        if (foundVar != m_configVariable.end())
        {
            // CVar already exist in memory (overriding)
            foundVar->second->ChangeValueString(value);
        }
        else
        {
            // CVar already doesn't exist in memory (inserting)
            RegisterNewConfigVariableFromString(key, value, cat);
        }
    }
}

void Configuration::RegisterNewConfigVariableFromString(const std::string& name,
                                                        const std::string& defaultValue,
                                                        const std::string& category)
{
    // Get the type from defaultValue string
    // Bool
    bool boolValue;
    if (ConfigurationUtils::IsBool(defaultValue, boolValue))
    {
        RegisterNewConfigVariable(name, boolValue, category);
        return;
    }

    // Int
    int intValue;
    if (ConfigurationUtils::IsInt(defaultValue, intValue))
    {
        RegisterNewConfigVariable(name, intValue, category);
        return;
    }

    // Double
    double doubleValue;
    if (ConfigurationUtils::IsDouble(defaultValue, doubleValue))
    {
        RegisterNewConfigVariable(name, doubleValue, category);
        return;
    }

    // Fall back to string value
    RegisterNewConfigVariable(name, defaultValue, category);
}
}  // namespace red
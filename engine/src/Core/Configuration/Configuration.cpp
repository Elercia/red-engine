#include "RedEngine/Core/Configuration/Configuration.hpp"
#include <RedEngine/Core/Configuration/IniReader.hpp>
#include <RedEngine/Core/Engine.hpp>
#include "RedEngine/Core/Configuration/CVar.hpp"

#include <string>
#include <utility>
#include <filesystem>

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

void Configuration::Init()
{
    auto& path = std::filesystem::current_path();
    RED_LOG_INFO("Started application in {}", path.u8string());

    CVar<std::string> userDataPath{"user_data_path", "common", m_resourceFolder};

    m_userDataFolder = userDataPath.GetValue();
}

void Configuration::ParseCommandLine(int argc, char** argv) {}

void Configuration::SetResourceFolder(std::string_view resourceFolder)
{
    m_resourceFolder = resourceFolder;
}

const std::string& Configuration::GetResourceFolder() const { return m_resourceFolder; }

const std::string& Configuration::GetUserDataFolder() const { return m_userDataFolder; }

void Configuration::LoadConfigFile(std::filesystem::path path)
{
    GetRedSubEngine<Configuration>()->LoadConfigFileInternal(std::move(path));
}

void Configuration::LoadConfigFileInternal(std::filesystem::path path)
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
            foundVar->second->ChangeValue(value);
        }
        else
        {
            // CVar already doesn't exist in memory (inserting)
            auto* cVarValue = new CVarValue(key, cat, value);
            m_configVariable.insert({ConfigurationUtils::GetLongName(cat, key), cVarValue});
        }
    }
}

CVarValue* Configuration::NewConsoleVariableDeclaration(const std::string& name,
                                                        const std::string& category,
                                                        const std::string& defaultValue)
{
    return GetRedSubEngine<Configuration>()->NewConsoleVariableDeclarationInternal(name, category,
                                                                                   defaultValue);
}

CVarValue* Configuration::NewConsoleVariableDeclarationInternal(const std::string& name,
                                                                const std::string& category,
                                                                const std::string& defaultValue)
{
    auto configName = ConfigurationUtils::GetLongName(category, name);
    auto foundConfigValue = m_configVariable.find(configName);
    if (foundConfigValue != m_configVariable.end())
    {
        return foundConfigValue->second;
    }

    auto* cVarValue = new CVarValue(name, category, defaultValue);
    m_configVariable.insert({configName, cVarValue});

    return cVarValue;
}
}  // namespace red
#include "RedEngine/Core/Configuration/CVarManager.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Engine.hpp"

#include <filesystem>
#include <string>
#include <utility>

namespace red
{
CVarManager& CVarManager::GetInstance()
{
    static CVarManager instance;

    return instance;
}

CVarManager::CVarManager()
{
}

CVarManager::~CVarManager()
{
    for (auto& pair : m_configVariable)
    {
        delete pair.second;
    }
}

void CVarManager::LoadConfigFileInternal(const Path& path)
{
    if(!path.Exist())
        return;

    auto iniCatKeyValues = utils::IniReader::ReadFromFile(path);

    for (auto& iniCatKeyValue : iniCatKeyValues)
    {
        auto& cat = std::get<0>(iniCatKeyValue);
        auto& key = std::get<1>(iniCatKeyValue);
        auto& value = std::get<2>(iniCatKeyValue);

        auto foundVar = m_configVariable.find(CVarUtils::GetLongName(cat, key));
        if (foundVar != m_configVariable.end())
        {
            // CVar already exist in memory (overriding)
            foundVar->second->ChangeValue(value);
        }
        else
        {
            // CVar already doesn't exist in memory (inserting)
            auto* cVarValue = new CVarValue(key, cat, value);
            m_configVariable.insert({CVarUtils::GetLongName(cat, key), cVarValue});
        }
    }
}

CVarValue* CVarManager::NewConsoleVariableDeclaration(const std::string& name, const std::string& category,
                                                      const std::string& defaultValue)
{
    return CVarManager::GetInstance().NewConsoleVariableDeclarationInternal(name, category, defaultValue);
}

void CVarManager::LoadConfigFile(const Path& path)
{
    CVarManager::GetInstance().LoadConfigFileInternal(path);
}

CVarValue* CVarManager::NewConsoleVariableDeclarationInternal(const std::string& name, const std::string& category,
                                                              const std::string& defaultValue)
{
    auto configName = CVarUtils::GetLongName(category, name);
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
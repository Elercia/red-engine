#include "RedEngine/Core/Configuration/CVarManager.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Engine.hpp"

#include <filesystem>
#include "RedEngine/Core/Container/String.hpp"
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
    if (!path.Exist())
        return;

    auto iniCatKeyValues = utils::IniReader::ReadFromFile(path);

    for (auto& iniCatKeyValue : iniCatKeyValues)
    {
        auto& cat = std::get<0>(iniCatKeyValue);
        auto& key = std::get<1>(iniCatKeyValue);
        auto& value = std::get<2>(iniCatKeyValue);

        auto* foundVar = FindCVar(CVarUtils::GetLongName(cat, key));
        if (foundVar != nullptr)
        {
            // CVar already exist in memory
            foundVar->ChangeValueFromString(value);
        }
        else
        {
            // CVar already doesn't exist
            // It is not registered and will not be usable
        }
    }
}

void CVarManager::LoadConfigFile(const Path& path)
{
    CVarManager::GetInstance().LoadConfigFileInternal(path);
}

ICVar* CVarManager::FindCVar(const String& fullName)
{
    auto it = m_configVariable.find(fullName);

    if (it == m_configVariable.end())
        return nullptr;

    return it->second;
}

}  // namespace red
#pragma once

#include "RedEngine/Core/Configuration/CVarSerialization.hpp"
#include "RedEngine/Core/Configuration/CVarUtils.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace red
{
template <typename Type>
class CVar;
class CVarValue;

class CVarManager
{
public:
    static CVarManager& GetInstance();

public:
    CVarManager();
    ~CVarManager();

    template <typename T>
    static void NewConsoleVariableDeclaration(CVar<T>* cvar, const std::string& name, const std::string& category,
                                              T defaultValue);

    static void LoadConfigFile(const Path& path);

private:
    void LoadConfigFileInternal(const Path& path);
    static CVarValue* NewConsoleVariableDeclaration(const std::string& name, const std::string& category,
                                                    const std::string& defaultValue);
    CVarValue* NewConsoleVariableDeclarationInternal(const std::string& name, const std::string& category,
                                                     const std::string& defaultValue);

    std::unordered_map<std::string, CVarValue*> m_configVariable;
    std::string m_resourceFolder;
    std::string m_userDataFolder;
};

}  // namespace red

#include "inl/CVarManager.inl"
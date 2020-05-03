#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <RedEngine/Core/SubEngine.hpp>
#include <RedEngine/Core/Configuration/ConfigurationSerializator.hpp>

namespace red
{
template <typename Type>
class CVar;
class CVarValue;

class Configuration : public SubEngine
{
public:
    Configuration();
    ~Configuration();

    void ParseCommandLine(int argc, char* argv[]);

    template <typename T>
    static void NewConsoleVariableDeclaration(CVar<T>* cvar, std::string name, std::string category,
                                              T defaultValue);

    static void LoadConfigFile(std::filesystem::path path);

private:
    void LoadConfigFileInternal(std::filesystem::path path);
    static CVarValue* NewConsoleVariableDeclaration(const std::string& name,
                                                    const std::string& category,
                                                    const std::string& defaultValue);
    CVarValue* NewConsoleVariableDeclarationInternal(const std::string& name,
                                                     const std::string& category,
                                                     const std::string& defaultValue);
    std::unordered_map<std::string, CVarValue*> m_configVariable;
};

}  // namespace red

#include "inl/Configuration.inl"
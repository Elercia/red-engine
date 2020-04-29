#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <RedEngine/Core/SubEngine.hpp>

namespace red
{
class ICVarValue;

template <class Type>
class CVar;
template <class Type>
class CVarValue;

class Configuration : public SubEngine
{
public:
    Configuration();
    ~Configuration();

    void LoadConfigFile(std::filesystem::path path);

    void ParseCommandLine(int argc, char* argv[]);

    template <typename T>
    void ChangeVar(std::string name, std::string category, T value);

    template <class Type>
    static void NewCVar(CVar<Type>* cvar, std::string name, Type defaultValue,
                        std::string category);

    static Configuration& GetInstance();

private:
    void RegisterNewConfigVariableFromString(const std::string& name,
                                             const std::string& defaultValue,
                                             const std::string& category);

    template <class Type>
    CVarValue<Type>* RegisterNewConfigVariable(const std::string& name, Type defaultValue,
                                               const std::string& category);

    std::unordered_map<std::string, ICVarValue*> m_configVariable;
};

}  // namespace red

#include "inl/Configuration.inl"
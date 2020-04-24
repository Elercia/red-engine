#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <RedEngine/Core/SubEngine.hpp>

#include "CVar.hpp"

namespace red
{
class ICVar;

class Configuration : public SubEngine
{
public:
    Configuration();
    ~Configuration();

    void LoadConfigFile(std::filesystem::path path);

    void ParseCommandLine(int argc, char* argv[]);

    void RegisterNewConfigVariable(ICVar* configVariable);

    template <typename T>
    void ChangeVar(std::string name, std::string category, T value);

    static void NewCVar(ICVar* configVariable);

    static Configuration& GetInstance();

private:
    std::unordered_map<std::string, ICVar*> m_configVariable;
};

}  // namespace red

#include "inl/Configuration.inl"
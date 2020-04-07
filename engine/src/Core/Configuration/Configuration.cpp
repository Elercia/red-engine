
#include <RedEngine/Core/Configuration/IniReader.hpp>
#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"

namespace red
{
Configuration::Configuration() {}

Configuration::~Configuration() {}

void Configuration::ParseCommandLine(int argc, char** argv) {}

void Configuration::RegisterNewConfigVariable(ICVar* configVariable)
{
    m_configVariable.insert({configVariable->GetLongName(), configVariable});
}

void Configuration::NewCVar(ICVar* configVariable)
{
    GetInstance().RegisterNewConfigVariable(configVariable);
}

Configuration& Configuration::GetInstance()
{
    static Configuration instance;
    return instance;
}

void Configuration::LoadConfigFile(std::filesystem::path path)
{
    auto iniCatKeyValues = utils::IniReader::ReadFromFile(path);

    for (auto& iniCatKeyValue : iniCatKeyValues)
    {
        auto& cat = std::get<0>(iniCatKeyValue);
        auto& key = std::get<1>(iniCatKeyValue);
        auto& value = std::get<2>(iniCatKeyValue);

        auto foundVar = m_configVariable.find(cat + "_" + key);
        if (foundVar != m_configVariable.end())
        {
            // CVar already exist in memory (overriding)
            foundVar->second->ChangeValue(value);
        }
        else
        {
            // CVar already doesn't exist in memory (inserting)
            // FIXME Need to add handle in the CVar to be able to keep the current arch
            //  Currently all the "m_configVariable" are const* because I passed "this" as a pointer
            //  Need to add a level of indirection to it
        }
    }
}
}  // namespace red
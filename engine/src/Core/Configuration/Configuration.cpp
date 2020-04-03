#include <RedEngine/Core/Configuration/CVar.hpp>
#include "RedEngine/Core/Engine.hpp"
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
}  // namespace red
#include "RedEngine/Core/Configuration/CVarUtils.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"

#include <cstdlib>

namespace red
{
std::string CVarUtils::GetLongName(const std::string& category, const std::string& key)
{
    return category + "_" + key;
}

std::string CVarUtils::GetLongName(const ICVar* cVar)
{
    return GetLongName(cVar->GetCategory(), cVar->GetName());
}
}  // namespace red

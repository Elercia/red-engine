#include "RedEngine/Core/Configuration/CVarUtils.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"

#include <cstdlib>

namespace red
{
String CVarUtils::GetLongName(const String& category, const String& key)
{
    return category + "_" + key;
}

String CVarUtils::GetLongName(const ICVar* cVar)
{
    return GetLongName(cVar->GetCategory(), cVar->GetName());
}
}  // namespace red

#include "RedEngine/Core/Configuration/CVar.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include <utility>

namespace red
{
String ICVar::GetName() const
{
    return m_name;
}

String ICVar::GetCategory() const
{
    return m_category;
}

String ICVar::GetLongName() const
{
    return CVarUtils::GetLongName(m_category, m_name);
}

ICVar::ICVar(const String& name, const String& category)
    : m_name(name), m_category(category)
{
}

void ICVar::ChangeValueFromString(const String& str)
{
    m_deserializationFunction(str);
}
}  // namespace red
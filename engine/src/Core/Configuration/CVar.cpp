#include "RedEngine/Core/Configuration/CVar.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include <utility>

namespace red
{
std::string ICVar::GetName() const
{
    return m_name;
}

std::string ICVar::GetCategory() const
{
    return m_category;
}

std::string ICVar::GetLongName() const
{
    return CVarUtils::GetLongName(m_category, m_name);
}

ICVar::ICVar(const std::string& name, const std::string& category, uint32 typeId)
    : m_name(name), m_category(category), m_typeId(typeId)
{
}

void ICVar::ChangeValueFromString(const std::string& str)
{
    m_deserializationFunction(str);
}
}  // namespace red
#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"

#include <utility>

namespace red
{
ICVarValue::ICVarValue(std::string name, std::string category)
    : m_name(std::move(name)), m_category(std::move(category))
{
}

std::string ICVarValue::GetName() const { return m_name; }
std::string ICVarValue::GetCategory() const { return m_category; }
std::string ICVarValue::GetLongName() const { return m_category + "_" + m_name; }
}  // namespace red
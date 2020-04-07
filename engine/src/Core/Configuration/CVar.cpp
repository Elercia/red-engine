#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"

#include <utility>

namespace red
{
ICVar::ICVar(std::string name, std::string category)
    : m_name(std::move(name)), m_category(std::move(category))
{
    Configuration::NewCVar(this);
}
std::string ICVar::GetName() const { return m_name; }
std::string ICVar::GetCategory() const { return m_category; }
std::string ICVar::GetLongName() const { return m_category + "_" + m_name; }
}  // namespace red
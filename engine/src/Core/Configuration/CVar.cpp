#include "RedEngine/Core/Configuration/CVar.hpp"

#include "RedEngine/Core/Configuration/Configuration.hpp"

#include <utility>

namespace red
{
CVarValue::CVarValue(std::string name, std::string category, std::string defaultValue)
    : m_defaultValue(std::move(defaultValue))
    , m_currentValue(m_defaultValue)
    , m_name(std::move(name))
    , m_category(std::move(category))
    , m_valueChangeCallback()
{
}

void CVarValue::ChangeValue(std::string newValue)
{
    m_currentValue = std::move(newValue);
    for (auto& func : m_valueChangeCallback)
    {
        func(this);
    }
}

void CVarValue::Reset() { ChangeValue(m_defaultValue); }

std::string CVarValue::GetName() const { return m_name; }

std::string CVarValue::GetCategory() const { return m_category; }

std::string CVarValue::GetLongName() const { return ConfigurationUtils::GetLongName(m_category, m_name); }
size_t CVarValue::OnValueChange(std::function<void(CVarValue*)> callback)
{
    auto index = m_valueChangeCallback.size();
    m_valueChangeCallback.push_back(std::move(callback));

    return index;
}
}  // namespace red
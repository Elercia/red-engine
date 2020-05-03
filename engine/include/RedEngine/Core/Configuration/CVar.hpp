#pragma once

#include <string>
#include <type_traits>
#include <functional>
#include <vector>

#include "Configuration.hpp"

namespace red
{
class CVarValue
{
    template <class Type>
    friend class CVar;
    friend Configuration;

public:
    CVarValue(std::string name, std::string category, std::string defaultValue);
    ~CVarValue() = default;

    void ChangeValue(std::string newValue);
    void Reset();

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::string GetCategory() const;
    [[nodiscard]] std::string GetLongName() const;

    size_t OnValueChange(std::function<void(CVarValue* variableValue)> callback);

private:
    std::string m_defaultValue;
    std::string m_currentValue;

    std::string m_name;
    std::string m_category;

    std::vector<std::function<void(CVarValue* variable)>> m_valueChangeCallback;
};

template <class Type>
class CVar
{
    friend CVarValue;
    friend Configuration;

public:
    CVar(std::string name, std::string category, Type defaultValue);
    ~CVar() = default;

    [[nodiscard]] inline Type GetValue();

    CVarValue* operator->();

private:
    CVarValue* m_value;
};

}  // namespace red

#include "inl/CVar.inl"
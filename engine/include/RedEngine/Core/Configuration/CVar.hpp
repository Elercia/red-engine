#pragma once

#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Event/Delegate.hpp"

#include <functional>
#include <string>
#include <type_traits>

namespace red
{
// Non-templated class to store genericly CVar into CVarManager
class ICVar
{
public:
    ICVar(const std::string& name, const std::string& category);
    virtual ~ICVar() = default;

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::string GetCategory() const;
    [[nodiscard]] std::string GetLongName() const;

    void ChangeValueFromString(const std::string& str);

protected:
    std::string m_name;
    std::string m_category;

    std::function<bool(const std::string&)> m_deserializationFunction;
};

// Shared CVar value managed by CVarManager
template <typename T>
class CVarValue : public ICVar
{
    template <class Type>
    friend class CVar;
    friend CVarManager;

public:
    using ValueChangeDelegate = Delegate<CVarValue<T>>;

    CVarValue(const std::string& name, const std::string& category, const T& defaultValue);
    virtual ~CVarValue() override = default;

    void ChangeValue(const T& newValue);
    void Reset();

    typename ValueChangeDelegate::FuncIndex OnValueChange(typename ValueChangeDelegate::FuncType callback);

private:
    const T m_defaultValue;
    T m_currentValue;

    ValueChangeDelegate m_changeDelegate;
};

// Holder class to declare CVar
// Creating a cvar will create a CVarValue of the given type inside CVarManager
template <class T>
class CVar
{
    friend CVarValue<T>;
    friend class CVarManager;

public:
    CVar(const std::string& name, const std::string& category, const T& defaultValue);
    CVar(CVarValue<T>* value);
    ~CVar() = default;

    [[nodiscard]] inline T& GetValue();
    void ChangeValue(const T& value);

    operator T();

    CVarValue<T>* operator->();

private:
    CVarValue<T>* m_value;
};

}  // namespace red

#include "inl/CVar.inl"
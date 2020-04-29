#pragma once

#include <string>
#include <type_traits>
#include <functional>

#include "../../Memory/ObjectHandle.hpp"
#include "Configuration.hpp"

namespace red
{
class ICVarValue
{
public:
    ICVarValue(std::string name, std::string category);
    virtual ~ICVarValue() = default;

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::string GetCategory() const;
    [[nodiscard]] std::string GetLongName() const;

    virtual void ChangeValueString(std::string newValueStr) = 0;

protected:
    std::string m_name;
    std::string m_category;
};

template <typename Type>
class CVarValue : public ICVarValue
{
    static_assert(std::is_copy_assignable<Type>::value);
    static_assert(std::is_copy_constructible<Type>::value);

public:
    CVarValue(std::string name, Type defaultValue, std::string category = "default");
    ~CVarValue() override = default;

    Type GetValue();

    void ChangeValueString(std::string newValueStr) override;
    void ChangeValue(Type newValue);
    void Reset();

    void RegisterChangeCallback(std::function<void(CVarValue<Type>* variable)> callback);

private:
    Type m_defaultValue;
    Type m_currentValue;

    std::function<void(CVarValue<Type>* variable)> m_valueChangeCallback;
};

template <class Type>
class CVar
{
    friend class Configuration;

public:
    CVar(std::string name, Type defaultValue, std::string category);
    ~CVar() = default;

    inline Type GetValue();

    inline void ChangeValueString(std::string newValueStr);
    inline void ChangeValue(Type newValue);
    inline void Reset();

    inline void RegisterChangeCallback(std::function<void(CVarValue<Type>* variable)> callback);

private:
    CVarValue<Type>* m_value;
};

}  // namespace red

#include "inl/CVar.inl"
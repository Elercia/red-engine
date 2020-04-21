#pragma once

#include <string>
#include <type_traits>
#include <functional>

#include "../../Memory/ObjectHandle.hpp"

namespace red
{
class ICVar
{
public:
    ICVar(std::string name, std::string category);
    ~ICVar() = default;

    std::string GetName() const;
    std::string GetCategory() const;
    std::string GetLongName() const;

    virtual void ChangeValue(std::string newValueStr) = 0;

protected:
    std::string m_name;
    std::string m_category;
};

template <typename Type>
class CVar : public ICVar
{
    static_assert(std::is_copy_assignable<Type>::value);
    static_assert(std::is_copy_constructible<Type>::value);

public:
    CVar(std::string name, Type defaultValue, std::string category = "default");
    ~CVar() = default;

    Type GetValue();

    void ChangeValue(std::string newValueStr) override;
    void ChangeValue(Type newValue);
    void Reset();

    void RegisterChangeCallback(std::function<void(CVar<Type>* variable)> callback);

private:
    Type m_defaultValue;
    Type m_currentValue;

    std::function<void(CVar<Type>* variable)> m_valueChangeCallback;
};
}  // namespace red

#include "inl/CVar.inl"
#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#define RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(CompClass) \
    class CompClass;                                         \
    red::Component* CreateCompoent_##CompClass(red::Entity* owner);

#define RED_COMPONENT_BASIC_FUNCTIONS_IMPL(CompClass)              \
    red::Component* CreateCompoent_##CompClass(red::Entity* owner) \
    {                                                              \
        return new CompClass(owner);                               \
    }

#define RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)           \
    using CompClassT = CompClass;                               \
    compData->componentTypeTraits = red::TypeInfo<CompClass>(); \
    compData->creator = &CreateCompoent_##CompClass;

#define RED_START_COMPONENT_REGISTER(CompClass)                             \
    virtual red::TypeTraits GetComponentTraits() const                      \
    {                                                                       \
        return red::TypeInfo<CompClass>();                                  \
    }                                                                       \
    static void RegisterComponentTypeTraits(red::ComponentTraits* compData) \
    {                                                                       \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)

#define RED_START_COMPONENT_REGISTER_INHERITHED(CompClass, InheritedCompClass) \
    virtual red::TypeTraits GetComponentTraits() const override                \
    {                                                                          \
        return red::TypeInfo<CompClass>();                                     \
    }                                                                          \
    static void RegisterComponentTypeTraits(red::ComponentTraits* compData)    \
    {                                                                          \
        InheritedCompClass::RegisterComponentTypeTraits(compData);             \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)                          \
        compData->inheritedComponentTraits = red::TypeInfo<InheritedCompClass>();

#define RED_END_COMPONENT_REGISTER()                                         \
    [[maybe_unused]] CompClassT* unused_but_suppress_warn_so_used = nullptr; \
    }

#define RED_MEMBER(name, memberAddr, tooltip, flags) compData->AddMember(name, &CompClassT::memberAddr, tooltip, flags);

namespace red
{
}

#include "inl/ComponentRegistryFunction.inl"
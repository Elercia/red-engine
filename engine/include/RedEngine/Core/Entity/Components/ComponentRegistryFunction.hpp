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

#define RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)              \
    using CompClassT = CompClass;                                  \
    compData->componentName = red::TypeInfo<CompClass>().name;     \
    compData->componentTypeId = red::TypeInfo<CompClass>().typeId; \
    compData->creator = &CreateCompoent_##CompClass;

#define RED_START_COMPONENT_REGISTER(CompClass)                             \
    virtual std::string_view GetComponentName() const                       \
    {                                                                       \
        return red::TypeInfo<CompClass>().name;                             \
    }                                                                       \
    static void RegisterComponentTypeTraits(red::ComponentTraits* compData) \
    {                                                                       \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)

#define RED_START_COMPONENT_REGISTER_INHERITHED(CompClass, InheritedCompClass) \
    virtual std::string_view GetComponentName() const override                 \
    {                                                                          \
        return red::TypeInfo<CompClass>().name;                                \
    }                                                                          \
    static void RegisterComponentTypeTraits(red::ComponentTraits* compData)    \
    {                                                                          \
        InheritedCompClass::RegisterComponentTypeTraits(compData);             \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)                          \
        compData->inheritedComponentName = red::TypeInfo<InheritedCompClass>().name;

#define RED_END_COMPONENT_REGISTER() }

#define RED_MEMBER(name, memberAddr, tooltip, flags) compData->AddMember(name, &CompClassT::memberAddr, tooltip, flags);

namespace red
{
}

#include "inl/ComponentRegistryFunction.inl"
#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#define RED_STATIC_COMPONENT_REGISTER_DATA(CompClass) compData->componentName = red::TypeInfo<CompClass>().name;

#define RED_START_COMPONENT_REGISTER(CompClass)                           \
    virtual std::string_view GetComponentName()                           \
    {                                                                     \
        return TypeInfo<CompClass>().name;                                \
    }                                                                     \
    static void RegisterComponentTypeTraits(red::ComponentData* compData) \
    {                                                                     \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)

#define RED_START_COMPONENT_REGISTER_INHERITHED(CompClass, InheritedCompClass) \
    std::string_view GetComponentName() override                               \
    {                                                                          \
        return TypeInfo<CompClass>().name;                                     \
    }                                                                          \
    static void RegisterComponentTypeTraits(red::ComponentData* compData)      \
    {                                                                          \
        InheritedCompClass::RegisterComponentTypeTraits(compData);             \
        RED_STATIC_COMPONENT_REGISTER_DATA(CompClass)                          \
        compData->inheritedComponentName = TypeInfo<InheritedCompClass>().name;

#define RED_END_COMPONENT_REGISTER() }

namespace red
{
}

#include "inl/ComponentRegistryFunction.inl"
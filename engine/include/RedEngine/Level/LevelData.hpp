#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"

namespace red
{
struct KeyValue
{
    std::string key;
    std::string value;
};

struct ComponentData
{
    Array<KeyValue> m_serializedMembers;
    std::string m_name;
};

struct EntityData
{
    Array<EntityData> m_children;
    Map<std::string, ComponentData> m_components;
    std::string m_name;
    EntityId m_id;
};

struct LevelData
{
    Array<EntityData> m_entities;
};

}  // namespace red
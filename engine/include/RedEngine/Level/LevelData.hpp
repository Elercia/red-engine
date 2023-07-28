#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
struct KeyValue
{
    String key;
    String value;
};

struct ComponentData
{
    Array<KeyValue> m_serializedMembers;
    String m_name;
};

struct EntityData
{
    Array<EntityData> m_children;
    Map<String, ComponentData> m_components;
    String m_name;
    EntityId m_id;
};

struct LevelData
{
    Array<EntityData> m_entities;
};

}  // namespace red
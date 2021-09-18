#include "RedEngine/Level/LevelSerializer.hpp"

#include "RedEngine/Filesystem/File.hpp"
#include "RedEngine/Level/Level.hpp"

#include <filesystem>
#include <fstream>

namespace red
{
ILevelSerializer::ILevelSerializer(const Level* level) : m_level(level)
{
}

bool ILevelSerializer::Serialize(const Path& path)
{
    // Generate the new level data
    bool success = true;
    LevelData levelData = GenerateLevelData(success);

    if (!success)
    {
        return false;
    }

    std::string serializedData = SerializeData(levelData);

    success = WriteToFile(path, serializedData);

    return success;
}

bool ILevelSerializer::WriteToFile(const Path& path, const std::string& str)
{
    File file(path, OpenMode::READ_WRITE_TC);

    if (!file.Open())
        return false;

    file.Write(str);

    file.Close();

    return true;
}

LevelData ILevelSerializer::GenerateLevelData(bool& success)
{
    LevelData levelData;

    for (auto* entity : m_level->GetRootEntity()->GetChildren())
    {
        EntityData entityData = SerializeEntity(success, entity);

        levelData.m_entities.push_back(entityData);
    }

    return levelData;
}

ComponentData ILevelSerializer::SerializeComponent(bool& success, const Component* component)
{
    ComponentData componentData;

    componentData.m_name = component->GetComponentName();

    const auto* compRegistry = component->GetWorld()->GetComponentRegistry();
    const auto* compTypeTraits = compRegistry->GetComponentTraits(std::string(component->GetComponentName()));

    if (compTypeTraits == nullptr)
    {
        RED_LOG_ERROR("Failed to serialize component {}. You forgot to register it",
                      std::string(component->GetComponentName()));

        success = false;

        return componentData;
    }

    for (auto& memberIt : compTypeTraits->members)
    {
        const auto serializedMember = memberIt.second.serializationFunction(component);

        componentData.m_serializedMembers.push_back({memberIt.first, serializedMember});
    }

    return componentData;
}

EntityData ILevelSerializer::SerializeEntity(bool& success, const Entity* entity)
{
    EntityData entityData;

    entityData.m_id = entity->GetId();
    entityData.m_name = entity->GetName();

    for (const auto* child : entity->GetChildren())
    {
        EntityData childData = SerializeEntity(success, child);

        entityData.m_children.push_back(childData);
    }

    for (const auto* component : entity->GetComponents())
    {
        ComponentData componentData = SerializeComponent(success, component);

        entityData.m_components.insert({componentData.m_name, componentData});
    }

    return entityData;
}
}  // namespace red

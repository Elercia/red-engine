#include "RedEngine/Level/JsonLevelSerializer.hpp"

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/JsonLevelData.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Level/LevelSerializer.hpp"

#include <fstream>
#include <iostream>
#include <utility>
namespace red
{
JsonLevelSerializer::JsonLevelSerializer(Level* level) : ILevelSerializer(level)
{
}

bool JsonLevelSerializer::SerializeToFile(const std::string& path)
{
    bool status = true;

    JsonLevelData levelData;

    for (auto* entity : m_level->m_rootEntity->GetChildren())
    {
        status = SerializeEntity(entity, levelData.AddLevelEntityData()) && status;
    }

    std::string levelStr = levelData.m_levelObject.dump(4);

    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::ostream os(&fb);
    os << levelStr;
    fb.close();

    return status;
}

bool JsonLevelSerializer::DeserializeFromFile(const std::string& path)
{
    std::string levelStr;
    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::istream os(&fb);
    os >> levelStr;
    fb.close();

    JsonLevelData levelData;
    levelData.m_levelObject = json::parse(levelStr);

    levelData.UpdateInternalDataFromReadJson();

    Array<JsonLevelComponentData> components;

    // Create empty entities (with only children)
    for (auto& jsonEntity : levelData.m_entities)
    {
        CreateEntityFrom(jsonEntity, components);
    }

    for (auto& jsonComp : components)
    {
        CreateComponentFrom(jsonComp);
    }

    return true;
}

bool JsonLevelSerializer::SerializeEntity(const Entity* entity, JsonLevelEntityData* entityData)
{
    bool status = true;

    entityData->SetId(entity->GetId());
    entityData->SetName(entity->GetName());

    for (auto* comp : entity->GetComponents())
    {
        status = SerializeComponent(comp, entityData->AddLevelComponentData(std::string(comp->GetComponentName()))) &&
                 status;
    }

    for (auto* child : entity->GetChildren())
    {
        status = SerializeEntity(child, entityData->AddLevelChildEntityData()) && status;
    }

    return status;
}

bool JsonLevelSerializer::SerializeComponent(const Component* comp, JsonLevelComponentData* compData)
{
    auto* compRegistry = comp->GetWorld()->GetComponentRegistry();

    const auto* compTypeTraits = compRegistry->GetComponentData(std::string(comp->GetComponentName()));

    if (compTypeTraits == nullptr)
    {
        RED_LOG_ERROR("Failed to serialize component {}. You forgot to register it",
                      std::string(comp->GetComponentName()));
        return false;
    }

    for (auto& memberIt : compTypeTraits->members)
    {
        auto str = memberIt.second.serializationFunction(comp);

        compData->AddPairOfValue(memberIt.second.name, str);
    }

    return true;
}

void JsonLevelSerializer::CreateEntityFrom(const JsonLevelEntityData& jsonEntity,
                                           Array<JsonLevelComponentData>& entityComponents)
{
    std::string name = jsonEntity.GetName();
    int id = jsonEntity.GetId();

    auto* entity = m_level->CreateEntity(id, name);

}

void JsonLevelSerializer::CreateComponentFrom(const JsonLevelComponentData& /*jsonComp*/)
{
}

}  // namespace red

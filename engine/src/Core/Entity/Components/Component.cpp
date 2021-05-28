#include "RedEngine/Core/Entity/Components/Component.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/LevelData.hpp"

namespace red
{
Component::Component(Entity* entity) : m_owner(entity), m_status()
{
}

Entity* Component::GetOwner() const
{
    return m_owner;
}

red::World* Component::GetWorld() const
{
    return m_owner->GetWorld();
}

void Component::Serialize(ILevelComponentData* levelComponentData) const
{
    auto* compRegistry = GetWorld()->GetComponentRegistry();

    const auto* compData = compRegistry->GetComponentData(std::string(GetComponentName()));

    if( compData == nullptr)
    {
        RED_LOG_ERROR("Failed to serialize component {}. You forgot to register it", std::string(GetComponentName()));
        return;
    }

    for (auto& memberIt : compData->members)
    {
        auto str = memberIt.second.serializationFunction(this);

        levelComponentData->AddPairOfValue(memberIt.second.name, str);
    }
}

void Component::Deserialize(const ILevelComponentData* /*levelComponentData*/)
{
}

}  // namespace red

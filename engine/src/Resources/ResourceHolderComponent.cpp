#include "RedEngine/Resources/ResourceHolderComponent.hpp"

namespace red
{
ResourceHolderComponent::ResourceHolderComponent(Entity* owner) : Component(owner) {}
ResourceHolderComponent::~ResourceHolderComponent()
{
    for (auto& resourceLoaderPair : m_resourceLoaders)
    {
        RED_SAFE_DELETE(resourceLoaderPair.second);
    }
}

bool ResourceHolderComponent::RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader)
{
    auto resourceLoaderIt = m_resourceLoaders.find(resourceType);

    if (resourceLoaderIt != m_resourceLoaders.end())
    {
        RED_ERROR("Resource loader already registered");
        return false;
    }

    RED_ASSERT(loader != nullptr, "Registered resource loader is null");

    m_resourceLoaders.insert({resourceType, loader});

    return true;
}

void ResourceHolderComponent::RemoveAllLoaders()
{
    for (auto& loader : m_resourceLoaders)
    {
        loader.second->FreeAllResources();
    }
    m_resourceLoaders.clear();
}

}  // namespace red
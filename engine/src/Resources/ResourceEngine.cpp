#include "RedEngine/Resources/ResourceEngine.hpp"

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine()
{
    for (auto& resourceLoaderPair : m_resourceLoaders)
    {
        RED_SAFE_DELETE(resourceLoaderPair.second);
    }
}

bool ResourceEngine::RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader)
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
}  // namespace red
#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <map>
#include <memory>
#include <string>

namespace red
{
class World;

class IResourceLoader
{
public:
    IResourceLoader(ResourceType resourceType, World* world);
    virtual ~IResourceLoader();

    const ResourceType GetResourceType() const;

protected:
    ResourceType m_resourceType;
    World* m_world;
};

template <typename IResourceType>
class ResourceLoader : public IResourceLoader
{
    static_assert(std::is_base_of_v<IResource, IResourceType>, "ResourceLoader template must inherit from Resource");

public:
    using Type = IResourceType;

    ResourceLoader(ResourceType resourceType, World* world);
    virtual ~ResourceLoader() = default;

    std::shared_ptr<IResourceType> GetFromCache(const std::string& name);
    std::shared_ptr<IResourceType> GetOrCreateFromCache(const std::string& name);

protected:
    std::map<ResourceId, std::shared_ptr<IResourceType>> m_loadedResources;
};

}  // namespace red

#include "inl/ResourceLoader.inl"
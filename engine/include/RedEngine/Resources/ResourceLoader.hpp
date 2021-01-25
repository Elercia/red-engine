#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <map>
#include <memory>
#include <string>

namespace red
{
class IResourceLoader
{
public:
    IResourceLoader(const std::string& name, ResourceType resourceType);
    virtual ~IResourceLoader();

    const std::string& GetResourceName() const;
    const ResourceType GetResourceType() const;

protected:
    std::string m_name;
    ResourceType m_resourceType;
};

template <typename IResourceType>
class ResourceLoader : public IResourceLoader
{
    static_assert(std::is_base_of_v<IResource, IResourceType>, "ResourceLoader template must inherit from Resource");

public:
    using Type = IResourceType;

    ResourceLoader(const std::string& name, ResourceType resourceType);
    virtual ~ResourceLoader() = default;

    std::shared_ptr<IResourceType> GetFromCache(const std::string& name);
    std::shared_ptr<IResourceType> GetOrCreateFromCache(const std::string& name);

protected:
    std::map<ResourceId, std::shared_ptr<IResourceType>> m_loadedResources;
};

}  // namespace red

#include "inl/ResourceLoader.inl"
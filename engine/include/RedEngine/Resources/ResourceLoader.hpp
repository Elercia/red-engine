#pragma once

#include "RedEngine/Filesystem/Path.hpp"
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

    ResourceType GetResourceType() const;

    virtual std::shared_ptr<IResource> LoadAbstractResource(const Path& path) = 0;

    virtual void FreeUnusedResources();
    virtual void FreeAllResources();

protected:
    ResourceType m_resourceType;
    World* m_world;
};

template <typename Type>
class ResourceLoader : public IResourceLoader
{
    static_assert(std::is_base_of_v<IResource, Type>, "ResourceLoader template must inherit from Resource");

public:
    using ThisType = Type;

    ResourceLoader(ResourceType resourceType, World* world);
    virtual ~ResourceLoader() = default;

    virtual std::shared_ptr<Type> LoadResource(const Path& path) = 0;
    virtual std::shared_ptr<IResource> LoadAbstractResource(const Path& path) override;
    virtual void FreeResource(std::shared_ptr<Type> resource) = 0;

    std::shared_ptr<Type> GetFromCache(const Path& path);
    std::shared_ptr<Type> GetOrCreateFromCache(const Path& path);

    virtual void FreeUnusedResources() override;
    virtual void FreeAllResources() override;

protected:
    std::map<Path, std::shared_ptr<Type>> m_loadedResources;
};

}  // namespace red

#include "inl/ResourceLoader.inl"
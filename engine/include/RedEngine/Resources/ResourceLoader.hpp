#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <memory>
#include <nlohmann/json.hpp>
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

    virtual void FinalizeUnusedResources() = 0;
    virtual void FinalizeAllResources() = 0;

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

    std::shared_ptr<IResource> LoadAbstractResource(const Path& path) override;
    std::shared_ptr<Type> LoadResource(const Path& path);

    virtual void FinalizeResource(std::shared_ptr<Type> resource) = 0;
    virtual bool InitResource(std::shared_ptr<Type>& resource, const Path& path, nlohmann::json jsonContent) = 0;

    std::shared_ptr<Type> GetFromCache(const Path& path);
    std::shared_ptr<Type> GetOrCreateFromCache(const Path& path);

    virtual void FinalizeUnusedResources() override;
    virtual void FinalizeAllResources() override;

protected:
    Map<Path, std::shared_ptr<Type>> m_loadedResources;
};

}  // namespace red

#include "inl/ResourceLoader.inl"
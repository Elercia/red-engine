#pragma

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"

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
    ResourceLoader(const std::string& name, ResourceType resourceType);
    virtual ~ResourceLoader() = 0;

    virtual std::shared_ptr<IResourceType> LoadResource(const std::string& name) = 0;
};
}  // namespace red

#include "inl/ResourceLoader.inl"
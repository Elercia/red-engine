#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <memory>

namespace red
{
class ResourceHolderComponent : public Component
{
public:
    ResourceHolderComponent(Entity* owner);
    ~ResourceHolderComponent();

    template <typename LoaderType>
    LoaderType* GetResourceLoader();

    template <typename T>
    std::shared_ptr<T> LoadResource(const Path& path, ResourceType resourceType);

    bool RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader);
    void RemoveAllLoaders();

private:
    Map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red

#include "inl/ResourceHolderComponent.inl"
#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <map>
#include <memory>
#include <vector>

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(ResourceHolderComponent)

class ResourceHolderComponent : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(ResourceHolderComponent, Component)
    RED_END_COMPONENT_REGISTER()

    ResourceHolderComponent(Entity* owner);
    ~ResourceHolderComponent();

    template <typename LoaderType>
    LoaderType* GetResourceLoader();

    template <typename T>
    std::shared_ptr<T> LoadResource(const Path& path, ResourceType resourceType);

    bool RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader);
    void RemoveAllLoaders();

private:
    std::map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red

#include "inl/ResourceHolderComponent.inl"
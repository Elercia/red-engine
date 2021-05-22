#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <map>
#include <memory>
#include <vector>

namespace red
{
class ResourceHolderComponent : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(ResourceHolderComponent, Component)
    RED_END_COMPONENT_REGISTER()

    ResourceHolderComponent(Entity* owner);
    ~ResourceHolderComponent();

    template <typename LoaderType>
    LoaderType* GetResourceLoader();

    bool RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader);

private:
    std::map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red

#include "inl/ResourceHolderComponent.inl"
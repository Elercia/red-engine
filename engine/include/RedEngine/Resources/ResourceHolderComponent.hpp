#pragma once

#include "RedEngine/Core/Components/Component.hpp"
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
    ResourceHolderComponent(Entity* owner);
    ~ResourceHolderComponent();

    template <typename LoaderType>
    LoaderType* GetResourceLoader();

    bool RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader);
    void RemoveAllLoaders();

private:
    std::map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red

#include "inl/ResourceHolderComponent.inl"
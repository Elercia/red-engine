#pragma once

#include <RedEngine/RedEngineBase.hpp>
#include <RedEngine/Core/SubEngine.hpp>
#include <RedEngine/Resources/Resource.hpp>
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <map>
#include <memory>
#include <vector>

namespace red
{
class ResourceEngine : public SubEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    template <typename LoaderType>
    LoaderType* GetResourceLoader();

    bool RegisterResourceLoader(ResourceType resourceType, IResourceLoader* loader);

private:
    std::map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red

#include "inl/ResourceEngine.inl"
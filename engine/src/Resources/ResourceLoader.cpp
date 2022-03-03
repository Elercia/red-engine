#include "RedEngine/Resources/ResourceLoader.hpp"

#include "RedEngine/Resources/ResourceModule.hpp"

namespace red
{
IResourceLoader::IResourceLoader(ResourceType resourceType, World* world) : m_resourceType(resourceType), m_world(world)
{
}

IResourceLoader::~IResourceLoader()
{
}

ResourceType IResourceLoader::GetResourceType() const
{
    return m_resourceType;
}

}  // namespace red
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
IResourceLoader::IResourceLoader(ResourceType resourceType, World* world) : m_resourceType(resourceType), m_world(world)
{
}

IResourceLoader::~IResourceLoader() {}

ResourceType IResourceLoader::GetResourceType() const { return m_resourceType; }

void IResourceLoader::FreeUnusedResources()
{
}

void IResourceLoader::FreeAllResources()
{
}

}  // namespace red
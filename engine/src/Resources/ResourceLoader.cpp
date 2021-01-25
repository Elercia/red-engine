#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
IResourceLoader::IResourceLoader(const std::string& name, ResourceType resourceType)
    : m_name(name), m_resourceType(resourceType)
{
}

IResourceLoader::~IResourceLoader() {}

const std::string& IResourceLoader::GetResourceName() const { return m_name; }

const ResourceType IResourceLoader::GetResourceType() const { return m_resourceType; }

}  // namespace red
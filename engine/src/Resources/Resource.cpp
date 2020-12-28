#include <RedEngine/Resources/Resource.hpp>

namespace red
{
IResource::IResource(ResourceId resourceId, ResourceType m_resourceType)
    : m_resourceId(resourceId), m_resourceType(m_resourceType), m_loadState(LoadState::STATE_NOT_LOADED)
{
}

IResource::~IResource() = default;

ResourceId IResource::GetResourceId() const { return m_resourceId; }

ResourceType IResource::GetResourceType() const { return m_resourceType; }

LoadState IResource::GetLoadState() const { return m_loadState; }

void IResource::SetLoadState(LoadState loadState) { m_loadState = loadState; }

}  // namespace red

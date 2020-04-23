#include <RedEngine/Resources/Resource.hpp>

namespace red
{
Resource::Resource(red::ResourceId resourceId, red::ResourceType::Enum m_resourceType)
    : m_resourceId(resourceId)
    , m_resourceType(m_resourceType)
    , m_loadState(LoadState::STATE_NOT_LOADED)
{
}

Resource::~Resource() = default;

ResourceId Resource::GetResourceId() const { return m_resourceId; }

ResourceType::Enum Resource::GetResourceType() const { return m_resourceType; }

LoadState::Enum Resource::GetLoadState() const { return m_loadState; }
}  // namespace red

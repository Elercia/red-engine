#include "RedEngine/Resources/Resource.hpp"

#include "RedEngine/Resources/ResourceModule.hpp"

namespace red
{
IResource::IResource(const Path& path, ResourceType m_resourceType)
    : m_resourcePath(path), m_resourceType(m_resourceType), m_loadState(LoadState::STATE_NOT_LOADED)
{
}

IResource::~IResource() = default;

const Path& IResource::GetResourcePath() const
{
    return m_resourcePath;
}

ResourceType IResource::GetResourceType() const
{
    return m_resourceType;
}

LoadState IResource::GetLoadState() const
{
    return m_loadState;
}

void IResource::SetLoadState(LoadState loadState)
{
    m_loadState = loadState;
}

}  // namespace red

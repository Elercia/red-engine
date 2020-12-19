#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <cstdint>
#include <cstddef>

namespace red
{
using ResourceId = std::size_t;

enum class LoadState
{
    STATE_NOT_LOADED,
    STATE_LOADED,
    STATE_ERROR
};

enum class ResourceType
{
    TEXTURE2D,
    AUDIO,
};

class IResource
{
public:
    IResource(ResourceId resourceId, ResourceType m_resourceType);
    virtual ~IResource();

    [[nodiscard]] ResourceId GetResourceId() const;
    [[nodiscard]] ResourceType GetResourceType() const;
    [[nodiscard]] LoadState GetLoadState() const;

    virtual void Release() = 0;

protected:
    ResourceId m_resourceId;
    ResourceType m_resourceType;
    LoadState m_loadState;
};

}  // namespace red
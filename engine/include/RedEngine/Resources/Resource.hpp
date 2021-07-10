#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace red
{
using ResourceId = std::string;

enum class LoadState
{
    STATE_NOT_LOADED,
    STATE_LOADED,
    STATE_ERROR
};

enum class ResourceType
{
    LEVEL,
    SPRITE,
    SOUND,
    TEXTURE2D,
    AUDIO,
};

#define RED_RESOURCE(Type) \
    static ResourceType GetResourceType() { return Type; }

class IResource
{
    friend class IResourceLoader;

public:
    IResource(ResourceId resourceId, ResourceType m_resourceType);
    virtual ~IResource();

    [[nodiscard]] ResourceId GetResourceId() const;
    [[nodiscard]] ResourceType GetResourceType() const;
    [[nodiscard]] LoadState GetLoadState() const;

    void SetLoadState(LoadState loadState);

protected:
    ResourceId m_resourceId;
    ResourceType m_resourceType;
    LoadState m_loadState;
};

}  // namespace red
#pragma once

#include <cstdint>

namespace red
{
using ResourceId = uint16_t;

struct LoadState
{
    enum Enum
    {
        STATE_NOT_LOADED,
        STATE_LOADED,
        STATE_ERROR
    };
};

struct ResourceType
{
    enum Enum
    {
        TEXTURE,
        AUDIO,
    };
};

class Resource
{
public:
    Resource(ResourceId resourceId, ResourceType::Enum m_resourceType);
    virtual ~Resource();

    [[nodiscard]] ResourceId GetResourceId() const;
    [[nodiscard]] ResourceType::Enum GetResourceType() const;
    [[nodiscard]] LoadState::Enum GetLoadState() const;

protected:
    const ResourceId m_resourceId;
    const ResourceType::Enum m_resourceType;
    LoadState::Enum m_loadState;
};

}  // namespace red
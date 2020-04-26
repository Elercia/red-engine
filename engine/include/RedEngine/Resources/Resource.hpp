#pragma once

#include <cstdint>

namespace red
{
using ResourceId_t = uint16_t;

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
        TEXTURE2D,
        AUDIO,
    };
};

class Resource
{
public:
    Resource(ResourceId_t resourceId, ResourceType::Enum m_resourceType);
    virtual ~Resource();

    [[nodiscard]] ResourceId_t GetResourceId() const;
    [[nodiscard]] ResourceType::Enum GetResourceType() const;
    [[nodiscard]] LoadState::Enum GetLoadState() const;

protected:
    const ResourceId_t m_resourceId;
    const ResourceType::Enum m_resourceType;
    LoadState::Enum m_loadState;
};

}  // namespace red
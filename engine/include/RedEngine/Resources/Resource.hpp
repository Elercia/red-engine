#pragma once

#include <cstdint>
#include <cstddef>

namespace red
{
using ResourceId_t = std::size_t;

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

    virtual void Release() = 0;

protected:
    const ResourceId_t m_resourceId;
    const ResourceType::Enum m_resourceType;
    LoadState::Enum m_loadState;
};

}  // namespace red
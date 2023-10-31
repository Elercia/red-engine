#pragma once

#include "RedEngine/Filesystem/Path.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace red
{
enum class LoadState
{
    STATE_NOT_LOADED,
    STATE_LOADED,
    STATE_RELEASED,
    STATE_ERROR
};

enum class ResourceType
{
    LEVEL,
    SPRITE,
    SOUND,
    TEXTURE2D,
    SHADER_PROGRAM,
    GEOMETRY,
    MATERIAL,
    AUDIO,
    FONT,
};

#define RED_RESOURCE(Type, EXT)                 \
    static ResourceType GetResourceType()       \
    {                                           \
        return Type;                            \
    }                                           \
    static std::wstring_view GetFileExtension() \
    {                                           \
        return EXT;                             \
    }

class IResource
{
    friend class IResourceLoader;

public:
    IResource(const Path& resourceId, ResourceType m_resourceType);
    virtual ~IResource();

    [[nodiscard]] const Path& GetResourcePath() const;
    [[nodiscard]] ResourceType GetResourceType() const;
    [[nodiscard]] LoadState GetLoadState() const;

    void SetLoadState(LoadState loadState);

protected:
    Path m_resourcePath;
    ResourceType m_resourceType;
    LoadState m_loadState;
};

}  // namespace red
#pragma once

#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class World;

class TextureResourceLoader : public ResourceLoader<Texture2D>
{
public:
    TextureResourceLoader(World* world);
    ~TextureResourceLoader();

    void FinalizeResource(std::shared_ptr<Texture2D> resource);
    bool InitResource(std::shared_ptr<Texture2D>& resource, const Path& path, nlohmann::json jsonContent);
};
}  // namespace red
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

    std::shared_ptr<Texture2D> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<red::Texture2D> resource) override;
};
}  // namespace red
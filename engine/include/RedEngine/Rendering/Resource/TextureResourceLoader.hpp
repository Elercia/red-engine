#pragma once

#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class TextureResourceLoader : public ResourceLoader<Texture2D>
{
public:
    TextureResourceLoader();
    ~TextureResourceLoader();

    std::shared_ptr<Texture2D> LoadResource(const std::string& name);
};
}  // namespace red
#pragma once

#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class World;

class MaterialResourceLoader : public ResourceLoader<Material>
{
public:
    MaterialResourceLoader(World* world);
    ~MaterialResourceLoader();

    std::shared_ptr<Material> LoadResource(const Path& path) override;

    void FreeResource(std::shared_ptr<Material> resource) override;
};
}  // namespace red
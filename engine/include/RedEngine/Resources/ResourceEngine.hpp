#pragma once

#include <map>
#include <memory>

#include <RedEngine/Resources/Resource.hpp>
#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Core/Components/Transform.hpp>

namespace red
{
class Texture2D;

class ResourceEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    static std::shared_ptr<Texture2D> LoadTexture(const std::string& path);

    void ReleaseTexture(Texture2D* texture, bool force = false);

private:
    std::shared_ptr<Texture2D> LoadTextureInternal(const std::string& path);

    void AddResourceToLoadedResources(ResourceType::Enum type,
                                      const std::shared_ptr<Texture2D>& resource);

    std::map<ResourceType::Enum, std::vector<std::shared_ptr<Resource>>> m_loadedResources;
};
}  // namespace red
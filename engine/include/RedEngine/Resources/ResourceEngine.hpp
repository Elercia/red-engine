#pragma once

#include <map>

#include <RedEngine/Resources/Resource.hpp>
#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Core/Components/Transform.hpp>

namespace red
{
class Texture;

class ResourceEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    static Texture* LoadTexture(const std::string& path);

    void ReleaseTexture(Texture* texture);

private:
    Texture* LoadTextureInternal(const std::string& path);
    void AddResourceToLoadedResources(ResourceType::Enum type, Resource* resource);

    std::map<ResourceType::Enum, std::vector<Resource*>> m_loadedResources;
};
}  // namespace red
#pragma once

#include <RedEngine/RedEngineBase.hpp>
#include <RedEngine/Core/SubEngine.hpp>
#include <RedEngine/Resources/Resource.hpp>
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <map>
#include <memory>
#include <vector>

namespace red
{
class ResourceEngine : public SubEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    template <typename IResourceType>
    ResourceLoader<IResourceType>* GetResourceLoader(ResourceType resourceType);

private:
    std::map<ResourceType, IResourceLoader*> m_resourceLoaders;
};

}  // namespace red


//    // static std::shared_ptr<Texture2D> CreateTextureFrom(SDL_Texture* sdlTexture);
//    static std::shared_ptr<Texture2D> LoadTexture(const std::string& resourceId);
//    static void LoadSprite(const std::string& resourceId, Sprite* sprite);
//
//    void ReleaseTexture(Texture2D* texture, bool erase = true);
//
//    void LoadLevel(const std::string& levelName);
//
//private:
//    std::shared_ptr<Texture2D> LoadTextureInternal(const std::string& resourceId);
//    // std::shared_ptr<Texture2D> CreateTextureFromInternal(SDL_Texture* sdlTexture);
//
//    void LoadSpriteInternal(const std::string& resourceId, Sprite* sprite);
//
//    void AddResourceToLoadedResources(ResourceType::Enum type,
//                                      const std::shared_ptr<Texture2D>& resource);
//
//    std::shared_ptr<Resource> GetResourceIfExist(ResourceType::Enum resourceType,
//                                                 ResourceId_t resourceId);
//
//    std::map<ResourceType::Enum, std::map<ResourceId_t, std::shared_ptr<Resource>>>
//        m_loadedResources;
//};

#include "inl/ResourceEngine.inl"
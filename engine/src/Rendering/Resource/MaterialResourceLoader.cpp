#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <GL/gl3w.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <stbi/stb_image.h>

namespace red
{
MaterialResourceLoader::MaterialResourceLoader(World* world) : ResourceLoader(ResourceType::TEXTURE2D, world)
{
}

MaterialResourceLoader::~MaterialResourceLoader()
{
}

std::shared_ptr<Material> MaterialResourceLoader::LoadResource(const Path& path)
{
    namespace fs = std::filesystem;

    auto resourcePtr = GetOrCreateFromCache(path);

    if (resourcePtr != nullptr && resourcePtr->GetLoadState() == LoadState::STATE_LOADED)
    {
        return resourcePtr;
    }

    resourcePtr->SetLoadState(LoadState::STATE_ERROR);  // At the end, the texture should either be
                                                        // loaded or not (if an error occurred)

    resourcePtr->SetLoadState(LoadState::STATE_LOADED);

    RED_LOG_INFO("Creating texture from path {}", path.GetAscciiPath());

    return resourcePtr;
}

void MaterialResourceLoader::FreeResource(std::shared_ptr<Material> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red
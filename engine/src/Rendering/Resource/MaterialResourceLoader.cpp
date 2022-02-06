#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

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
    using json = nlohmann::json;

    Path activePath = path;
    activePath.Append(L".json");

    auto resourcePtr = GetOrCreateFromCache(activePath);

    if (resourcePtr != nullptr && resourcePtr->GetLoadState() == LoadState::STATE_LOADED)
    {
        return resourcePtr;
    }

    resourcePtr->SetLoadState(LoadState::STATE_ERROR);  // At the end, the texture should either be
                                                        // loaded or not (if an error occurred)

    if (!activePath.Exist() || activePath.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load material for path {}", activePath.GetAscciiPath());
        return resourcePtr;
    }

    auto* shaderResourceLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<ShaderProgramResourceLoader>();

    auto parsedJson = json::parse(ReadFile(activePath), nullptr, false);

    resourcePtr->m_shaderProgram = shaderResourceLoader->LoadResource(Path(parsedJson["shader_program"]));

    resourcePtr->m_type = parsedJson["rendering_type"];

    resourcePtr->SetLoadState(LoadState::STATE_LOADED);

    RED_LOG_INFO("Creating material from path {}", activePath.GetAscciiPath());

    return resourcePtr;
}

void MaterialResourceLoader::FreeResource(std::shared_ptr<Material> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red
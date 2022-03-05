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

bool MaterialResourceLoader::InitResource(std::shared_ptr<Material>& resource, const Path& /*path*/,
                                          nlohmann::json jsonContent)
{
    auto* shaderResourceLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<ShaderProgramResourceLoader>();

    std::string shaderPathStr = jsonContent["shader_program"];
    Path shaderPath = Path::Resource(shaderPathStr);
    resource->m_shaderProgram = shaderResourceLoader->LoadResource(shaderPath);

    resource->m_type = jsonContent["rendering_type"];

    return true;
}

void MaterialResourceLoader::FinalizeResource(std::shared_ptr<Material> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);

    resource->m_shaderProgram = NULL;
}

}  // namespace red
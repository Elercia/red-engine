#include "RedEngine/Rendering/Resource/FontResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

namespace red
{
FontResourceLoader::FontResourceLoader(World* world) : ResourceLoader<Font>(ResourceType::GEOMETRY, world)
{
}

FontResourceLoader::~FontResourceLoader()
{
}

bool FontResourceLoader::InitResource(std::shared_ptr<Font>& resource, const Path& /*path*/, nlohmann::json jsonContent)
{
    auto* textureResourceLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<TextureResourceLoader>();

    std::vector<nlohmann::json> glyphsArray = jsonContent["glyphs"];
    nlohmann::json atlasJson = jsonContent["atlas"];

    std::string pathStr = atlasJson["path"];
    Path atlasPath = Path::Resource(pathStr);
    
    resource->m_atlas = textureResourceLoader->LoadResource(atlasPath);
    resource->m_size = atlasJson["size"];
    resource->m_pixelRange = atlasJson["distanceRange"];

    float height = atlasJson["height"];
    float width = atlasJson["width"];

    for (nlohmann::json glyphJson : glyphsArray)
    {
        GlyphCode unicodeCode = glyphJson["unicode"];
        float advance = glyphJson["advance"];

        Glyph& glyph = resource->m_glyphs[unicodeCode];
        glyph.advance = advance;

        if (glyphJson.find("atlasBounds") != glyphJson.end())
        {
            nlohmann::json atlasBoundsJson = glyphJson["atlasBounds"];

            glyph.atlasBounds.x = atlasBoundsJson["top"] / height;
            glyph.atlasBounds.y = atlasBoundsJson["left"] / width;
            glyph.atlasBounds.z = atlasBoundsJson["bottom"] / height;
            glyph.atlasBounds.w = atlasBoundsJson["right"] / width;
        }

        if (glyphJson.find("planeBounds") != glyphJson.end())
        {
            nlohmann::json planeBoundsJson = glyphJson["planeBounds"];

            glyph.planeBounds.x = planeBoundsJson["top"];
            glyph.planeBounds.y = planeBoundsJson["left"];
            glyph.planeBounds.z = planeBoundsJson["bottom"];
            glyph.planeBounds.w = planeBoundsJson["right"];
        }
    }

    return true;
}

void FontResourceLoader::FinalizeResource(std::shared_ptr<Font> /*resource*/)
{
}
}  // namespace red
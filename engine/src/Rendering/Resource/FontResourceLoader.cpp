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
    std::vector<nlohmann::json> glyphsArray = jsonContent["glyphs"];

    auto* textureResourceLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<TextureResourceLoader>();

    for (nlohmann::json glyphJson : glyphsArray)
    {
        GlyphCode unicodeCode = glyphJson["unicode"];
        float advance = glyphJson["advance"];

        Glyph& glyph = resource->m_glyphs[unicodeCode];
        glyph.advance = advance;

        if (glyphJson.find("atlasBounds") != glyphJson.end())
        {
            nlohmann::json atlasBoundsJson = glyphJson["atlasBounds"];

            glyph.atlasBounds.x = atlasBoundsJson["top"];
            glyph.atlasBounds.y = atlasBoundsJson["left"];
            glyph.atlasBounds.z = atlasBoundsJson["bottom"];
            glyph.atlasBounds.w = atlasBoundsJson["right"];
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

    nlohmann::json atlasJson = jsonContent["atlas"];
    std::string pathStr = atlasJson["path"];
    Path atlasPath = Path::Resource(pathStr);
    resource->m_atlas = textureResourceLoader->LoadResource(atlasPath);

    return true;
}

void FontResourceLoader::FinalizeResource(std::shared_ptr<Font> /*resource*/)
{
}
}  // namespace red
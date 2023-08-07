#pragma once

#include "RedEngine/Rendering/Resource/Font.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class World;

class FontResourceLoader : public ResourceLoader<Font>
{
public:
    FontResourceLoader(World* world);
    ~FontResourceLoader();

    virtual void FinalizeResource(std::shared_ptr<Font> resource) override;
    virtual bool InitResource(std::shared_ptr<Font>& resource, const Path& path, nlohmann::json jsonContent) override;
};
}  // namespace red
#pragma once

#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class LevelResourceLoader : public ResourceLoader<Level>
{
public:
    LevelResourceLoader(World* world);
    virtual ~LevelResourceLoader();

    std::shared_ptr<Level> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<red::Level> resource) override;
};
}  // namespace red
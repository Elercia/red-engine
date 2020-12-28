#pragma once

#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class LevelResourceLoader : public ResourceLoader<Level>
{
public:
    LevelResourceLoader();
    virtual ~LevelResourceLoader();

    std::shared_ptr<Level> LoadResource(const std::string& name);
};
}  // namespace red
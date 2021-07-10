#include "RedEngine/Level/LevelResourceLoader.hpp"

namespace red
{
LevelResourceLoader::LevelResourceLoader(World* world) : ResourceLoader(ResourceType::LEVEL, world) {}
LevelResourceLoader::~LevelResourceLoader() {}

std::shared_ptr<Level> LevelResourceLoader::LoadResource(const std::string& /*name*/) { return nullptr; }


void LevelResourceLoader::FreeResource(std::shared_ptr<red::Level> /*resource*/)
{
    RED_ABORT("Unimplmented");
}

}  // namespace red
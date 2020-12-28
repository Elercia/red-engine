#include <RedEngine/Level/LevelResourceLoader.hpp>

namespace red
{
LevelResourceLoader::LevelResourceLoader() : ResourceLoader("Level", ResourceType::LEVEL) {}
LevelResourceLoader::~LevelResourceLoader() {}

std::shared_ptr<Level> LevelResourceLoader::LoadResource(const std::string& name) { return nullptr; }

}  // namespace red
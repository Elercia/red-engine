#pragma once

#include <memory>
#include <vector>
#include <RedEngine/Core/SubEngine.hpp>

namespace red
{
class Sprite;

class ResourceEngine : public SubEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    bool ImportSprite(Sprite* sprite);
    void FreeSprite(Sprite* mesh);

private:
};
}  // namespace red
#pragma once

#include <memory>
#include <vector>

namespace red
{
class RenderingEngine;
class Sprite;

class ResourceEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    bool ImportSprite(Sprite* sprite);
    void FreeSprite(Sprite* mesh);

private:
};
}  // namespace red
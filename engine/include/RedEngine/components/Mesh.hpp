#pragma once

#include <string>

#include <RedEngine/ecs/Component.hpp>

namespace red
{
class Mesh : public Component
{
public:
    RED_COMPONENT('MESH')
    Mesh(Entity* entity, std::string path);

private:
    std::string m_path;
};
}  // namespace red

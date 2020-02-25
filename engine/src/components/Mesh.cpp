#include <RedEngine/components/Mesh.hpp>
#include <utility>


namespace red
{
Mesh::Mesh(Entity* entity, std::string path) : Component(entity), m_path(std::move(path)) {}
}
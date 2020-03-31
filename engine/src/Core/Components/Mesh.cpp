#include "RedEngine/Core/Components/Mesh.hpp"

#include <utility>

namespace red
{
Mesh::Mesh(Entity* entity, std::string path)
    : Component(entity), m_isLoaded(LoadState::NOT_LOADED), m_path(std::move(path))
{
}
}  // namespace red
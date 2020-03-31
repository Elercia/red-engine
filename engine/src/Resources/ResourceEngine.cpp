#include <RedEngine/Core/Components/Mesh.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
ResourceEngine::ResourceEngine() : m_meshes() {}
ResourceEngine::~ResourceEngine() {}

bool ResourceEngine::ImportMesh(Mesh* mesh)
{
    mesh->SetLoadedState(LoadState::LOADED);

    return true;
}
void ResourceEngine::FreeMesh(Mesh* mesh) {}
}  // namespace red
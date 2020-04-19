#include <RedEngine/Core/Components/Mesh.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Debug/Debug.hpp>

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine() {}

bool ResourceEngine::ImportMesh(Mesh* mesh)
{
    mesh->SetLoadedState(LoadState::LOADED);

    return true;
}
void ResourceEngine::FreeMesh(Mesh* mesh) {}
}  // namespace red
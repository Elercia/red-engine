#pragma once

#include <memory>
#include <vector>

namespace red
{
class Mesh;

class ResourceEngine
{
public:
    ResourceEngine();
    ~ResourceEngine();

    bool ImportMesh(Mesh* mesh);
    void FreeMesh(Mesh* mesh);

private:
    std::vector<Mesh*> m_meshes;
};
}  // namespace red
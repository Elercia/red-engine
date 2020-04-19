#pragma once

#include <memory>
#include <vector>

namespace red
{
class Mesh;

class ResourceEngine
{

    friend Mesh;

public:
    ResourceEngine();
    ~ResourceEngine();

    bool ImportMesh(Mesh* mesh);
    void FreeMesh(Mesh* mesh);

private:

};
}  // namespace red
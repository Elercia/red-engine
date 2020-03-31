#pragma once

#include <string>
#include <vector>

#include "../../Math/Vector.hpp"
#include "Component.hpp"

namespace red
{
struct LoadState
{
    enum Enum
    {
        NOT_LOADED,
        LOADED,
        IN_ERROR
    };
};

class Mesh : public Component
{
    RED_COMPONENT("MESH")
public:
    Mesh(Entity* entity, std::string path);

    void SetVertices(std::vector<Vector3> vertices) { m_vertices = std::move(vertices); };
    void SetIndices(std::vector<int> indices) { m_indices = std::move(indices); };

    std::string GetPath() { return m_path; };

    void SetLoadedState(LoadState::Enum state) { m_isLoaded = state; }
    LoadState::Enum GetLoadedState() { return m_isLoaded; }

private:
    LoadState::Enum m_isLoaded;
    std::string m_path;

    std::vector<Vector3> m_vertices;
    std::vector<int> m_indices;
};
}  // namespace red

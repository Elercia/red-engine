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
        ERROR
    };
};

class Mesh : public Component
{
    RED_COMPONENT("MESH")

    friend class ResourceEngine;

public:
    Mesh(Entity* entity, std::string path);

    std::string GetPath() { return m_path; };

    void SetLoadedState(LoadState::Enum state) { m_isLoaded = state; }
    LoadState::Enum GetLoadedState() { return m_isLoaded; }

private:
    LoadState::Enum m_isLoaded;
    std::string m_path;
};
}  // namespace red

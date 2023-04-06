#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"

namespace red
{
class ExecutionGraph;
class Entity;
}

namespace perf
{

class PerfLevel : public red::Level
{
public:
    explicit PerfLevel(red::World* world) : red::Level("PerfLevel", world), m_manager(nullptr){};
    ~PerfLevel() override = default;

    void Init() override;
    void Finalize() override;

    virtual void AddGameplaySystems(red::ExecutionGraph& graph) override;

private:
    void AddEntity(const std::string& name, const red::Vector2& v, red::RenderLayerIndex i, red::Color* colors);

    red::Entity* m_manager;
};
}  // namespace perf

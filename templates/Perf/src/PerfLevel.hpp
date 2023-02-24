#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"

namespace perf
{
class PerfLevel : public red::Level
{
public:
    explicit PerfLevel(red::World* world) : red::Level("PerfLevel", world){};
    ~PerfLevel() override = default;

    void Init() override;
    void Finalize() override;

private:
    void AddEntity(const std::string& name, const red::Vector2& v, red::RenderLayerIndex i, red::Color* colors);
};
}  // namespace perf

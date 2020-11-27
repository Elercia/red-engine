#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <RedEngine/Core/Entity/System.hpp>

namespace red
{
class RenderingEngine;

class DebugSystem : public System
{
public:
    explicit DebugSystem(World* world);
    ~DebugSystem() override = default;

    void LateUpdate() override;

private:
    RenderingEngine* m_renderingEngine;
};
}  // namespace red

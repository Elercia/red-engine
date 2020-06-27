#pragma once

#include <RedEngine/Core/Components/Component.hpp>
#include <RedEngine/Math/Vector.hpp>

#include <vector>

namespace red
{
class DebugComponent : public Component
{
    friend class DebugSystem;

public:
    explicit DebugComponent(Entity* entity);
    ~DebugComponent() override = default;

    void AddLine(const Vector2& from, const Vector2& to);

private:
    std::vector<std::pair<Vector2, Vector2>> m_frameDebugLines;
};
}  // namespace red

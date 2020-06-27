#include <RedEngine/Debug/Component/DebugComponent.hpp>

namespace red
{
DebugComponent::DebugComponent(Entity* entity) : Component(entity), m_frameDebugLines() {}
void DebugComponent::AddLine(const Vector2& from, const Vector2& to)
{
    m_frameDebugLines.emplace_back(from, to);
}

}  // namespace red

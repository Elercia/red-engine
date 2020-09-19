#include <RedEngine/Core/Debug/Component/DebugComponent.hpp>
#include <RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp>

namespace red
{
DebugComponent::DebugComponent(Entity* entity)
    : Component(entity), m_frameShapes(), m_physicsDebugDrawer(nullptr)
{
}
void DebugComponent::AddLine(const Vector2& from, const Vector2& to,
                             Color c /* = ColorConstant::BLACK */)
{
    auto segment = new DebugSegment{DebugShapeType::SEGMENT, false, c, from, to};
    m_frameShapes.emplace_back(segment);
}

void DebugComponent::AddCircle(const Vector2& center, float radius,
                               Color c /*= ColorConstant::BLACK*/)
{
    auto circle = new DebugCircle{DebugShapeType::CIRCLE, false, c, center, radius};
    m_frameShapes.emplace_back(circle);
}

void DebugComponent::AddPolygon(const std::vector<Vector2>& points,
                                Color c /*= ColorConstant::BLACK*/)
{
    auto polygon = new DebugPolygon{DebugShapeType::POLYGON, false, c, points};
    m_frameShapes.emplace_back(polygon);
}

}  // namespace red
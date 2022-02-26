#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(DebugComponent)

DebugComponent::DebugComponent(Entity* entity) : Component(entity), m_physicsDebugDrawer(nullptr)
{
}

void DebugComponent::AddLine(const Vector2& from, const Vector2& to, const Color& c /* = ColorConstant::BLACK */)
{
    auto* segment = new DebugSegment{{DebugShapeType::SEGMENT, false, c}, from, to};
    m_frameShapes.emplace_back(segment);
}

void DebugComponent::AddCircle(const Vector2& center, float radius, const Color& c /*= ColorConstant::BLACK*/)
{
    auto* circle = new DebugCircle{{DebugShapeType::CIRCLE, false, c}, center, radius};
    m_frameShapes.emplace_back(circle);
}

void DebugComponent::AddPolygon(const Array<Vector2>& points, const Color& c /*= ColorConstant::BLACK*/,
                                bool isSolid /*= false*/)
{
    auto* polygon = new DebugPolygon{{DebugShapeType::POLYGON, isSolid, c}, std::move(points)};
    m_frameShapes.emplace_back(polygon);
}

void DebugComponent::AddPoint(const Vector2& coord, const Color& c /*= ColorConstant::BLACK*/, bool isSolid /*= false*/)
{
    auto* point = new DebugPoint{{DebugShapeType::POINT, isSolid, c}, coord};
    m_frameShapes.emplace_back(point);
}
}  // namespace red

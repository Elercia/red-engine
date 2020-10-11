#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"

#include <vector>

namespace red
{
PhysicsDebugDrawer::PhysicsDebugDrawer(DebugComponent* debugComponent)
    : b2Draw(), m_debugComponent(debugComponent)
{
}

PhysicsDebugDrawer::~PhysicsDebugDrawer() = default;

void PhysicsDebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                                     const b2Color& color)
{
    std::vector<Vector2> points;

    for (int32 i = 0; i < vertexCount; i++)
    {
        points.push_back(ConvertFromPhysicsVector(vertices[i]));
    }

    m_debugComponent->AddPolygon(
        points, {uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255)});
}

void PhysicsDebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                          const b2Color& color)
{
    std::vector<Vector2> points;

    for (int i = 0; i < vertexCount; i++)
    {
        points.push_back(ConvertFromPhysicsVector(vertices[i]));
    }

    m_debugComponent->AddPolygon(
        points, {uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255)});
}

void PhysicsDebugDrawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    m_debugComponent->AddCircle(
        ConvertFromPhysicsVector(center), radius,
        {uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255)});
}

void PhysicsDebugDrawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis,
                                         const b2Color& color)
{
    m_debugComponent->AddCircle(
        ConvertFromPhysicsVector(center), radius,
        {uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255)});
}

void PhysicsDebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    m_debugComponent->AddLine(
        ConvertFromPhysicsVector(p1), ConvertFromPhysicsVector(p2),
        {uint8_t(color.r * 255), uint8_t(color.g * 255), uint8_t(color.b * 255)});
}

void PhysicsDebugDrawer::DrawTransform(const b2Transform& xf)
{
    m_debugComponent->AddCircle(ConvertFromPhysicsVector(xf.p), 1.f, ColorConstant::BLACK);
}

}  // namespace red
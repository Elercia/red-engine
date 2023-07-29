#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"

namespace red
{
PhysicsDebugDrawer::PhysicsDebugDrawer(DebugComponent* debugComponent) : m_debugComponent(debugComponent)
{
}

PhysicsDebugDrawer::~PhysicsDebugDrawer() = default;

void PhysicsDebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Array<Vector2, DoubleLinearArrayAllocator> points;

    points.reserve(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
    {
        points.push_back(ConvertFromPhysicsVector(vertices[i]));
    }

    m_debugComponent->AddPolygon(ArrayView(points),
                                 Color(color.r, color.g, color.b));
}

void PhysicsDebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Array<Vector2, DoubleLinearArrayAllocator> points;

    points.reserve(vertexCount);
    for (int i = 0; i < vertexCount; i++)
    {
        points.push_back(ConvertFromPhysicsVector(vertices[i]));
    }

    m_debugComponent->AddPolygon(ArrayView(points),
                                 Color(color.r, color.g, color.b), true);
}

void PhysicsDebugDrawer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    m_debugComponent->AddCircle(ConvertFromPhysicsVector(center), ConvertFromPhysicsDistance(radius),
                                Color(color.r, color.g, color.b));
}

void PhysicsDebugDrawer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& /*axis*/,
                                         const b2Color& color)
{
    m_debugComponent->AddCircle(ConvertFromPhysicsVector(center), ConvertFromPhysicsDistance(radius),
                                Color(color.r, color.g, color.b));
}

void PhysicsDebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    m_debugComponent->AddLine(ConvertFromPhysicsVector(p1), ConvertFromPhysicsVector(p2),
                              Color(color.r, color.g, color.b));
}

void PhysicsDebugDrawer::DrawTransform(const b2Transform& xf)
{
    m_debugComponent->AddPoint(ConvertFromPhysicsVector(xf.p), ColorConstant::BLACK);
}

void PhysicsDebugDrawer::DrawPoint(const b2Vec2& p, float /*size*/, const b2Color& color)
{
    m_debugComponent->AddPoint(ConvertFromPhysicsVector(p),
                               Color(color.r, color.g, color.b));
}

}  // namespace red
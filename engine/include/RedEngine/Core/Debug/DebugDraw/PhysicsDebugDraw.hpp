#pragma once

#include <box2d/b2_draw.h>
#include <box2d/box2d.h>

namespace red
{
class DebugComponent;

class PhysicsDebugDrawer : public b2Draw
{
public:
    explicit PhysicsDebugDrawer(DebugComponent* debugComponent);
    ~PhysicsDebugDrawer();

    /// Draw a closed polygon provided in CCW order.
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

    /// Draw a solid closed polygon provided in CCW order.
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

    /// Draw a circle.
    virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;

    /// Draw a solid circle.
    virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;

    /// Draw a line segment.
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

    /// Draw a transform. Choose your own length scale.
    /// @param xf a transform.
    virtual void DrawTransform(const b2Transform& xf) override;

    /// Draw a point.
    virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

private:
    DebugComponent* m_debugComponent;
};

}  // namespace red
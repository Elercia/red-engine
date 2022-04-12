#pragma once

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"

#include <memory>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
enum class DebugShapeType
{
    SEGMENT,
    POLYGON,
    CIRCLE,
    POINT
};

struct DebugShape
{
    DebugShapeType type;
    bool isFilled;
    Color color;
};

struct DebugCircle : public DebugShape
{
    Vector2 center;
    float radius;
};

struct DebugSegment : public DebugShape
{
    Vector2 point1;
    Vector2 point2;
};

struct DebugPolygon : public DebugShape
{
    Array<Vector2> points;
};

struct DebugPoint : public DebugShape
{
    Vector2 coord;
};

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(DebugComponent)

// TODO Add console component (add utilities like "console debug (OR should I make a 'log into console bool ?')")
class DebugComponent : public Component
{
    friend class DebugSystem;
    friend class RenderingSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(DebugComponent, Component)
    RED_END_COMPONENT_REGISTER()

    explicit DebugComponent(Entity* entity);
    ~DebugComponent() override = default;

    void AddLine(const Vector2& from, const Vector2& to, const Color& c = ColorConstant::BLACK);
    void AddCircle(const Vector2& center, float radius, const Color& c = ColorConstant::BLACK);
    void AddPolygon(const Array<Vector2>& points, const Color& c = ColorConstant::BLACK, bool isSolid = false);
    void AddPoint(const Vector2& coord, const Color& c = ColorConstant::BLACK, bool isSolid = false);

    void ClearLogs();
    const Array<std::string>& GetLogBuffer() const;
    void HandleCommand(const std::string& str);
    void AddLog(const std::string& str);

private:
    Array<std::unique_ptr<DebugShape>> m_frameShapes;
    std::unique_ptr<PhysicsDebugDrawer> m_physicsDebugDrawer;
    Array<std::string> m_logs;
};
}  // namespace red

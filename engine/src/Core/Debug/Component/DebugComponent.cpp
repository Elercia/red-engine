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
    auto* polygon = new DebugPolygon{{DebugShapeType::POLYGON, isSolid, c}, points};
    m_frameShapes.emplace_back(polygon);
}

void DebugComponent::AddPoint(const Vector2& coord, const Color& c /*= ColorConstant::BLACK*/, bool isSolid /*= false*/)
{
    auto* point = new DebugPoint{{DebugShapeType::POINT, isSolid, c}, coord};
    m_frameShapes.emplace_back(point);
}

void DebugComponent::ClearLogs()
{
    m_logs.clear();
}

const Array<Logger::LogOoutputInfo>& DebugComponent::GetLogBuffer() const
{
    return m_logs;
}

void DebugComponent::HandleCommand(const std::string& str)
{
    Logger::LogOoutputInfo info;
    info.str = str;
    info.level = LogLevel::LEVEL_CUSTOM;
    m_logs.push_back(info);
}

void DebugComponent::AddLog(const Logger::LogOoutputInfo& str)
{
    m_logs.push_back(str);
    if (m_logs.size() > 1000)
        m_logs.erase(m_logs.begin(), m_logs.begin() + 100);
}
}  // namespace red

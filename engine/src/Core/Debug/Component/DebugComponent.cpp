#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(DebugComponent)

DebugComponent::DebugComponent(Entity* entity)
    : Component(entity), m_lineShaderProgram(nullptr), m_physicsDebugDrawer(nullptr)
{
    m_lineShaderProgram = m_owner->GetWorld()
                              ->GetWorldComponent<ResourceHolderComponent>()
                              ->GetResourceLoader<ShaderProgramResourceLoader>()
                              ->LoadResource(Path::Resource("ENGINE_RESOURCES/LINE_SHADER_PROGRAM"));
}

// TODO Add solid debug draw

void DebugComponent::AddLine(const Vector2& from, const Vector2& to, const Color& c /* = ColorConstant::BLACK */)
{
    m_debugLines.push_back({from, c});
    m_debugLines.push_back({to, c});
}

void DebugComponent::AddCircle(const Vector2& center, float radius, const Color& c /*= ColorConstant::BLACK*/)
{
    // Draw a cicle by approching it by "nbLines" lines
    // Each points of this approximation is drawn with a certain angle.
    constexpr int nbLines = 30;

    const float stepAngle = Math::PI / (float) nbLines;
    for (int i = 0; i <= nbLines; i++)
    {
        const float startAngle = stepAngle * (float) i;
        const float endAngle = stepAngle * (float) (i + 1);

        const Vector2 startPoint(center.x + radius * Math::Cos(startAngle), center.y + radius * Math::Sin(startAngle));
        const Vector2 endPoint(center.x + radius * Math::Cos(endAngle), center.y + radius * Math::Sin(endAngle));

        AddLine(startPoint, endPoint, c);
    }
}

void DebugComponent::AddPolygon(const ArrayView<Vector2>& points, const Color& c /*= ColorConstant::BLACK*/,
                                bool /*isSolid*/ /*= false*/)
{
    for (uint32 i = 0; i < points.size(); i++)
    {
        AddLine(points[i], points[(i + 1) % points.size()], c);
    }
}

void DebugComponent::AddPoint(const Vector2& coord, const Color& c /*= ColorConstant::BLACK*/, bool /*isSolid*/ /*= false*/)
{
    AddCircle(coord, 0.1f, c);
}

std::shared_ptr<ShaderProgram> DebugComponent::GetLineShader()
{
    return m_lineShaderProgram;
}

const Array<DebugLinePoint>& DebugComponent::GetDebugLines() const
{
    return m_debugLines;
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

Array<Entity*>& DebugComponent::GetFilteredEntities()
{
    return m_filteredEntities;
}
}  // namespace red

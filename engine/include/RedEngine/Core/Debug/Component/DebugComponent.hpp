#pragma once

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"

#include <memory>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
class ShaderProgram;
class Text;

struct DebugLinePoint
{
    Vector4 pos;
    Color color;
};

using DebugMenuDrawerFunc = void(*)(DebugComponent*);

struct DebugDrawer
{
    int id;
    std::string name;
    DebugMenuDrawerFunc callback;
};

class DebugComponent : public Component
{
    friend class DebugSystem;
    friend class RenderingSystem;

public:
    explicit DebugComponent(Entity* entity);
    ~DebugComponent() = default;

    void AddLine(const Vector2& from, const Vector2& to, const Color& c = ColorConstant::BLACK);
    void AddCircle(const Vector2& center, float radius, const Color& c = ColorConstant::BLACK);
    void AddPolygon(const ArrayView<Vector2>& points, const Color& c = ColorConstant::BLACK, bool isSolid = false);
    void AddPoint(const Vector2& coord, const Color& c = ColorConstant::BLACK, bool isSolid = false);

    int AddDebugDrawer(const char* name, DebugMenuDrawerFunc&& callback);
    void RemoveDebugDrawer(int id);

    std::shared_ptr<ShaderProgram> GetLineShader();
    const Array<DebugLinePoint>& GetDebugLines() const;
    void ClearDebug();

    void ClearLogs();
    const Array<Logger::LogOoutputInfo>& GetLogBuffer() const;
    void HandleCommand(const std::string& str);
    void AddLog(const Logger::LogOoutputInfo& str);
    Array<Entity*>& GetFilteredEntities();

private:

    std::shared_ptr<ShaderProgram> m_lineShaderProgram;

    Array<DebugLinePoint> m_debugLines;

    std::unique_ptr<PhysicsDebugDrawer> m_physicsDebugDrawer;
    Array<Logger::LogOoutputInfo> m_logs;
    Array<DebugDrawer> m_drawers;
    Array<Entity*> m_filteredEntities;

    Text* m_fpsText;
};
}  // namespace red

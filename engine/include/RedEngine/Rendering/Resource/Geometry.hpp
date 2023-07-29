#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Resources/Resource.hpp"

namespace red
{
enum class PrimitiveType
{
    TRIANGLE,
    QUAD,
    LINES,
    POINTS,
    // GL_LINE_LOOP,
    // GL_LINE_STRIP,
    // GL_TRIANGLE_STRIP,
    // GL_TRIANGLE_FAN,
};

class Geometry
{
    friend class GeometryResourceLoader;
    friend class Renderer;

public:
    Geometry();
    ~Geometry();

    PrimitiveType GetPrimitiveType() const;

    int GetIndexeCount() const;
    int GetVertexCount() const;

private:
    uint32 m_gpuBufferHandle{(uint32) -1};  // Vao handle
    uint32 m_gpuIndexBuffer{(uint32) -1};   // IBO Handle

    int m_indexCount{0};
    int m_vertexCount{0};
    PrimitiveType m_primitiveType{PrimitiveType::TRIANGLE};
};

// Wrapper class to handle resources as a geometry (to not duplicated geometry from resources) but that keep Geomtry
// free from being manually created
class GeometryResourceWrapper : public IResource
{
    friend class GeometryResourceLoader;

public:
    RED_RESOURCE(ResourceType::GEOMETRY, L"geometry");

    GeometryResourceWrapper(const Path& resourceId);
    ~GeometryResourceWrapper();

    Geometry m_geom;
};
}  // namespace red

#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Resources/Resource.hpp"

namespace red
{
enum class PrimitiveType
{
    TRIANGLE,
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

    void Create(int vertexCount, float* vertexData, float* uvData, int indexCount, int* indexData, PrimitiveType type);
    void Destroy();

private:
    uint32 m_vaoHandle;
    uint32 m_iboHandle;
    uint32 m_vboHandle;
    uint32 m_uvHandle;

    int m_indexCount;
    int m_vertexCount;
    PrimitiveType m_primitiveType;
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

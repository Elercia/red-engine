#include "RedEngine/Rendering/Resource/Geometry.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Resources/Resource.hpp"

#include <GL/gl3w.h>

namespace red
{
Geometry::Geometry()
    : m_vaoHandle((uint32) -1)
    , m_iboHandle((uint32) -1)
    , m_vboHandle((uint32) -1)
    , m_uvHandle((uint32) -1)
    , m_indexCount(0)
    , m_vertexCount(0)
    , m_primitiveType(PrimitiveType::TRIANGLE)
{
}

Geometry::~Geometry()
{
}

PrimitiveType Geometry::GetPrimitiveType() const
{
    return m_primitiveType;
}

int Geometry::GetIndexeCount() const
{
    return m_indexCount;
}

int Geometry::GetVertexCount() const
{
    return m_vertexCount;
}

void Geometry::Create(int vertexCount, float* vertexData, float* uvData, int indexCount, int* indexData, PrimitiveType type)
{
    m_vertexCount = vertexCount;
    m_indexCount = indexCount;
    m_primitiveType = type;

    constexpr int floatPerVertex = 3;  // TODO size of 2
    constexpr int floatPerUv = 2;

    glGenBuffers(1, &m_vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * floatPerVertex, vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &m_uvHandle);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvHandle);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * floatPerUv, uvData, GL_STATIC_DRAW);

    glGenBuffers(1, &m_iboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(int), indexData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vaoHandle);
    glBindVertexArray(m_vaoHandle);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, floatPerVertex, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_uvHandle);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, floatPerUv, GL_FLOAT, GL_FALSE, 0, 0);
}

void Geometry::Destroy()
{
    uint32 buffers[4] = {m_vboHandle, m_iboHandle, m_uvHandle};
    glDeleteBuffers(4, buffers);

    glDeleteVertexArrays(1, &m_vaoHandle);

    m_vaoHandle = (uint32) -1;
    m_vboHandle = (uint32) -1;
    m_iboHandle = (uint32) -1;
    m_uvHandle = (uint32) -1;

    m_indexCount = 0;
    m_vertexCount = 0;
}

GeometryResourceWrapper::GeometryResourceWrapper(const Path& resourceId) : IResource(resourceId, ResourceType::GEOMETRY)
{
}

GeometryResourceWrapper::~GeometryResourceWrapper()
{
}
}  // namespace red

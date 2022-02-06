#include "RedEngine/Rendering/Resource/Geometry.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Resources/Resource.hpp"

namespace red
{
Geometry::Geometry()
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

GeometryResourceWrapper::GeometryResourceWrapper(const Path& resourceId) : IResource(resourceId, ResourceType::GEOMETRY)
{
}

GeometryResourceWrapper::~GeometryResourceWrapper()
{
}
}  // namespace red

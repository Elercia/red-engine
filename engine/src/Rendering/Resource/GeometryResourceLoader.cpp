#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <GL/gl3w.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

namespace red
{
GeometryResourceLoader::GeometryResourceLoader(World* world)
    : ResourceLoader<GeometryResourceWrapper>(ResourceType::GEOMETRY, world)
{
}

GeometryResourceLoader::~GeometryResourceLoader()
{
}

bool GeometryResourceLoader::InitResource(std::shared_ptr<GeometryResourceWrapper>& resource, const Path& /*path*/,
                                          nlohmann::json jsonContent)
{
    // FIXME : Use Array class
    auto jsonVertex = jsonContent["vertices"].get<std::vector<float>>();
    auto jsonIndex = jsonContent["indexes"].get<std::vector<int>>();
    auto jsonUvs = jsonContent["uvs"].get<std::vector<float>>();

    RED_LOG_INFO("Loaded {} vertices, {} indexes, {} uvs", jsonVertex.size(), jsonIndex.size(), jsonUvs.size());

    auto& geom = resource->m_geom;

    geom.m_indexCount = (int) jsonIndex.size();
    geom.m_vertexCount = (int) jsonVertex.size();
    geom.m_primitiveType = jsonContent["primitive_type"];

    geom.Create((int) jsonVertex.size(), jsonVertex.data(), jsonUvs.data(), (int) jsonIndex.size(), jsonIndex.data(),
                PrimitiveType::TRIANGLE);

    return true;
}

void GeometryResourceLoader::FinalizeResource(std::shared_ptr<GeometryResourceWrapper> resource)
{
    resource->m_geom.Destroy();
}
}  // namespace red
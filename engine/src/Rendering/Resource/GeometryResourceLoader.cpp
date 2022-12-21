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

    geom.m_indexCount = (int)jsonIndex.size();
    geom.m_vertexCount = (int)jsonVertex.size();
    geom.m_primitiveType = jsonContent["primitive_type"];

    GLuint vertex_vbo = 0;
    glGenBuffers(1, &vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, jsonVertex.size() * sizeof(float), jsonVertex.data(), GL_STATIC_DRAW);

    GLuint uv_vbo = 0;
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, jsonUvs.size() * sizeof(float), jsonUvs.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &geom.m_gpuIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom.m_gpuIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, jsonIndex.size() * sizeof(int), jsonIndex.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &geom.m_gpuBufferHandle);
    glBindVertexArray(geom.m_gpuBufferHandle);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // TODO size of 2

    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    return true;
}

void GeometryResourceLoader::FinalizeResource(std::shared_ptr<GeometryResourceWrapper> /*resource*/)
{
}
}  // namespace red
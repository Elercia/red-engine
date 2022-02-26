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

std::shared_ptr<GeometryResourceWrapper> GeometryResourceLoader::LoadResource(const Path& path)
{
    using json = nlohmann::json;

    Path activePath = path;
    activePath.Append(L".json");

    auto geometryResource = GetOrCreateFromCache(activePath);

    if (geometryResource->GetLoadState() == LoadState::STATE_LOADED)
        return geometryResource;

    if (!activePath.Exist() || activePath.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load geometry for path {}", activePath.GetAscciiPath());
        return nullptr;
    }

    auto parsedJson = json::parse(ReadFile(activePath), nullptr, false, true);

    if (parsedJson.is_discarded() || !parsedJson.is_array())
    {
        RED_LOG_WARNING("Path {} is not a valid JSON", activePath.GetAscciiPath());
        return nullptr;
    }

    // FIXME : Use Array class 
    auto jsonVertex = parsedJson["vertices"].get<std::vector<float>>();
    auto jsonIndex = parsedJson["indexes"].get<std::vector<float>>();
    auto jsonUvs = parsedJson["uv"].get<std::vector<float>>();

    auto& geom = geometryResource->m_geom;

    geom.m_indexCount = (int)jsonIndex.size();
    geom.m_vertexCount = (int)jsonVertex.size();
    geom.m_primitiveType = parsedJson["primitive_type"];

    GLuint vertex_vbo = 0;
    glGenBuffers(1, &vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, jsonVertex.size() * sizeof(float), jsonVertex.data(), GL_STATIC_DRAW);

    GLuint index_ibo = 0;
    glGenBuffers(1, &index_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, jsonIndex.size() * sizeof(int), jsonIndex.data(), GL_STATIC_DRAW);

    GLuint uv_vbo = 0;
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, jsonUvs.size() * sizeof(float), jsonUvs.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &geom.m_gpuBufferHandle);
    glBindVertexArray(geom.m_gpuBufferHandle);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_ibo);
    glVertexAttribPointer(3, 2, GL_INT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(3);

    geometryResource->SetLoadState(LoadState::STATE_LOADED);

    return geometryResource;
}

void GeometryResourceLoader::FreeResource(std::shared_ptr<GeometryResourceWrapper> /*resource*/)
{
}
}  // namespace red
#pragma once

#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class World;

class GeometryResourceLoader : public ResourceLoader<GeometryResourceWrapper>
{
public:
    GeometryResourceLoader(World* world);
    ~GeometryResourceLoader();

    std::shared_ptr<GeometryResourceWrapper> LoadResource(const Path& path) override;

    void FreeResource(std::shared_ptr<GeometryResourceWrapper> resource) override;
};
}  // namespace red
#pragma once

namespace red
{
class GeometryResourceLoader : public ResourceLoader<Geometry>
{
public:
	GeometryResourceLoader(World* world);
    ~GeometryResourceLoader();

    std::shared_ptr<Geometry> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<Geometry> resource) override;
};
}
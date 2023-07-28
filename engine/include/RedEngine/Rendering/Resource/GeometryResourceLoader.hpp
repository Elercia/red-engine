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
    
    virtual void FinalizeResource(std::shared_ptr<GeometryResourceWrapper> resource) override;
    virtual bool InitResource(std::shared_ptr<GeometryResourceWrapper>& resource, const Path& path,
                              Json jsonContent) override;
};
}  // namespace red
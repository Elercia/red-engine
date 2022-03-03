#pragma once

#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class ShaderProgramResourceLoader : public ResourceLoader<ShaderProgram>
{
public:
    ShaderProgramResourceLoader(World* world);
    ~ShaderProgramResourceLoader();

    virtual void FinalizeResource(std::shared_ptr<ShaderProgram> resource) override;
    virtual bool InitResource(std::shared_ptr<ShaderProgram>& resource, const Path& path, nlohmann::json jsonContent) override;

private:
    enum class ShaderType
    {
        Pixel,
        Vertex,
        Compute
    };

    int CompileShader(ShaderType type, const Path& path);
};

}  // namespace red
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

    std::shared_ptr<ShaderProgram> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<ShaderProgram> resource) override;

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
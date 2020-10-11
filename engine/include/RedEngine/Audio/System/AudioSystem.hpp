#pragma once

#include "RedEngine/Core/Entity/System.hpp"

#include <FMOD/fmod.hpp>
#include <FMOD/fmod_studio.hpp>

namespace red
{
class AudioSystem : public System
{
public:
    AudioSystem(World* world);
    ~AudioSystem();

    virtual void Init() override;
    virtual void Finalise() override;

    virtual void Update() override;

private:
    FMOD::Studio::System* systemFmod;
};

}  // namespace red
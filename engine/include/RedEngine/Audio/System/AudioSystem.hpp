#pragma once

#include "RedEngine/Audio/AudioModule.hpp"

#include "RedEngine/Core/Entity/System.hpp"

#include <fmod.hpp>
#include <fmod_studio.hpp>

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

    FMOD::System* GetFmodSystem();

private:
    FMOD::Studio::System* m_studioSystem;
    FMOD::System* m_system;
};

}  // namespace red
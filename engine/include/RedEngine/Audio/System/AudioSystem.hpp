#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/RedEngineBase.hpp"

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

private:
    FMOD::Studio::System* m_studioSystem;
    FMOD::System* m_system;
};

}  // namespace red
#pragma once

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <vector>

namespace red
{
class AudioSource : public Component
{
    friend class AudioSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(AudioSource, Component)
    RED_END_COMPONENT_REGISTER()

    AudioSource(Entity* owner);
    ~AudioSource() = default;

    void PlaySound(const SoundDesc& sound);

private:
    std::vector<SoundDesc> m_soundPlayQueue;
};

}  // namespace red
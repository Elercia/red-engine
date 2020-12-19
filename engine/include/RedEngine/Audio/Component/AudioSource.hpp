#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include "RedEngine/Core/Components/Component.hpp"

#include "RedEngine/Audio/AudioEvent.hpp"

#include <vector>

namespace red
{
class AudioSource : public Component
{
    friend class AudioSystem;

public:
    AudioSource(Entity* owner);
    ~AudioSource() = default;

    void PlaySound(const SoundDesc& sound);

private:
    std::vector<SoundDesc> m_soundPlayQueue;
};

}  // namespace red
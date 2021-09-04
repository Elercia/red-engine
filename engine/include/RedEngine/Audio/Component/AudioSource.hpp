#pragma once

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/RedEngineBase.hpp"

namespace FMOD
{
class Channel;
}

namespace red
{
class SoundResource;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(AudioSource)

class AudioSource : public Component
{
    friend class AudioSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(AudioSource, Component)
    RED_END_COMPONENT_REGISTER()

    AudioSource(Entity* owner);
    AudioSource(Entity* owner, SoundDesc desc);
    ~AudioSource() = default;

    void Play();
    void Stop();
    void Pause();
    void UnPause();
    void Loop(int loopCount = -1);

    std::shared_ptr<SoundResource> GetResource()
    {
        return m_sound;
    }

private:
    SoundDesc m_desc;

    std::shared_ptr<SoundResource> m_sound = nullptr;
    FMOD::Channel* m_currentChannel = nullptr;

    bool m_needStart = false;
    bool m_needStop = false;
    bool m_needPause = false;
    bool m_needUnpause = false;
};

}  // namespace red
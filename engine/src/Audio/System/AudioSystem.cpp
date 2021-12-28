#include "RedEngine/Audio/System/AudioSystem.hpp"

#include "RedEngine/Audio/AudioModule.hpp"
#include "RedEngine/Audio/AudioUtils.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Audio/Resource/SoundResource.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Time/Time.hpp"

namespace red
{
AudioSystem::AudioSystem(World* world) : System(world), m_studioSystem(nullptr), m_system(nullptr)
{
}

AudioSystem::~AudioSystem() = default;

void AudioSystem::Init()
{
    System::Init();

    FmodUtils::FmodCheck(FMOD::Studio::System::create(&m_studioSystem), "Creating FMOD studio system");
    FmodUtils::FmodCheck(m_studioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL),
                         "Initializing FMOD studio system");
    FmodUtils::FmodCheck(m_studioSystem->getCoreSystem(&m_system), "Get core system");
}

void AudioSystem::Finalise()
{
    FmodUtils::FmodCheck(m_studioSystem->unloadAll(), "Unloading");
    FmodUtils::FmodCheck(m_studioSystem->release(), "Release");
}

void AudioSystem::Update()
{
    // Update listeners
    for (auto* audioListenerEntity : GetComponents<AudioListener>())
    {
        auto* audioListener = audioListenerEntity->GetComponent<AudioListener>();
        auto* audioListenerTransform = audioListenerEntity->GetComponent<Transform>();

        FMOD_VECTOR oldPos = FmodUtils::Convert(audioListener->m_lastFramePos);
        FMOD_VECTOR currentPos = FmodUtils::Convert(audioListenerTransform->GetPosition());
        audioListener->m_lastFramePos = audioListenerTransform->GetPosition();

        FMOD_VECTOR velocity;
        velocity.x = (currentPos.x - oldPos.x) * (1000 / Time::DeltaTime());
        velocity.y = (currentPos.y - oldPos.y) * (1000 / Time::DeltaTime());
        velocity.z = 0;

        FMOD_VECTOR forward;
        forward.x = 1;
        forward.y = 0;
        forward.z = 0;

        FMOD_VECTOR up;
        up.x = 0;
        up.z = 1;
        up.y = 0;

        FMOD_3D_ATTRIBUTES attributes = {{0}};
        attributes.position = currentPos;
        attributes.velocity = velocity;
        attributes.forward = forward;
        attributes.up = up;
        FmodUtils::FmodCheck(m_studioSystem->setListenerAttributes(audioListener->m_listenerId, &attributes),
                             "Set listener attributes");
    }

    // Update audio sources
    for (auto* entity : GetComponents<AudioSource>())
    {
        auto* audioSource = entity->GetComponent<AudioSource>();
        auto resource = audioSource->GetResource();

        if (resource->GetLoadState() != LoadState::STATE_LOADED)
        {
            continue;
        }

        if (audioSource->m_needStart)
        {
            m_system->playSound(resource->GetSound(), nullptr, false, &audioSource->m_currentChannel);
        }
        audioSource->m_needStart = false;

        if (audioSource->m_currentChannel != nullptr)
        {
            if (audioSource->m_needStop)
            {
                FmodUtils::FmodCheck(audioSource->m_currentChannel->stop(), "failed to stop sound");
            }
            audioSource->m_needStop = false;

            if (audioSource->m_needPause)
            {
                FmodUtils::FmodCheck(audioSource->m_currentChannel->setPaused(true), "failed to pause sound");
            }
            audioSource->m_needPause = false;

            if (audioSource->m_needUnpause)
            {
                FmodUtils::FmodCheck(audioSource->m_currentChannel->setPaused(false), "failed to un-pause sound");
            }
            audioSource->m_needUnpause = false;
        }
    }

    FmodUtils::FmodCheck(m_system->update(), "FMOD system update");
}

FMOD::System* AudioSystem::GetFmodSystem()
{
    return m_system;
}

}  // namespace red
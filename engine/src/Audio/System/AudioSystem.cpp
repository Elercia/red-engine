#include "RedEngine/Audio/System/AudioSystem.hpp"

#include "RedEngine/Audio/AudioUtils.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Core/Time/Time.hpp"

namespace red
{
AudioSystem::AudioSystem(World* world) : System(world), m_studioSystem(nullptr), m_system(nullptr) {}

AudioSystem::~AudioSystem() = default;

void AudioSystem::Init()
{
    FmodCheck(FMOD::Studio::System::create(&m_studioSystem), "Creating FMOD studio system");
    FmodCheck(m_studioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL),
              "Initializing FMOD studio system");
    FmodCheck(m_studioSystem->getCoreSystem(&m_system), "Get core system");
}

void AudioSystem::Finalise()
{
    FmodCheck(m_studioSystem->unloadAll(), "Unloading");
    FmodCheck(m_studioSystem->release(), "Release");
}

void AudioSystem::Update()
{
    FMOD::Channel* channel1 = nullptr;

    for (auto* audioListenerEntity : GetComponents<AudioListener>())
    {
        auto* audioListener = audioListenerEntity->GetComponent<AudioListener>();
        auto* audioListenerTransform = audioListenerEntity->GetComponent<Transform>();

        FMOD_VECTOR oldPos = audioListener->m_fmodVect;
        ConvertRef(audioListener->m_fmodVect, audioListenerTransform->GetPosition());

        FMOD_VECTOR velocity;
        velocity.x = (audioListener->m_fmodVect.x - oldPos.x) * (1000 / Time::DeltaTime());
        velocity.y = (audioListener->m_fmodVect.y - oldPos.y) * (1000 / Time::DeltaTime());
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
        attributes.position = audioListener->m_fmodVect;
        attributes.velocity = velocity;
        attributes.forward = forward;
        attributes.up = up;
        FmodCheck(m_studioSystem->setListenerAttributes(audioListener->m_listenerId, &attributes),
                  "Set listener attributes");

        for (auto* entity : GetComponents<AudioSource>())
        {
            // auto* transform = entity->GetComponent<Transform>();
            auto* audioSource = entity->GetComponent<AudioSource>();

            for (auto& sound : audioSource->m_soundPlayQueue)
            {
                (void) sound;
                FMOD::Sound* sound1;
                m_system->createSound("resources/sample.mp3", FMOD_2D, 0, &sound1);

                m_system->playSound(sound1, 0, false, &channel1);
            }

            audioSource->m_soundPlayQueue.clear();
        }

        FmodCheck(m_system->update(), "Fmod system update");
    }
}

}  // namespace red
#include "RedEngine/Audio/Component/AudioSource.hpp"

namespace red
{
AudioSource::AudioSource(Entity* owner) : Component(owner), m_soundPlayQueue() {}

void AudioSource::PlaySound(const SoundDesc& sound) { m_soundPlayQueue.push_back(sound); }
}  // namespace red

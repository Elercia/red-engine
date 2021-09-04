#include "RedEngine/Audio/Resource/SoundResource.hpp"

namespace red
{
SoundResource::SoundResource(const Path& path) : IResource(path, ResourceType::AUDIO), m_sound(nullptr)
{
}

SoundResource::~SoundResource()
{
}

FMOD::Sound* SoundResource::GetSound()
{
    return m_sound;
}

void SoundResource::SetSound(FMOD::Sound* sound)
{
    m_sound = sound;
}

}  // namespace red

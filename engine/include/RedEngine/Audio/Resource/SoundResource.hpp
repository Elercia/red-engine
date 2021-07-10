#pragma once

#include "RedEngine/Resources/Resource.hpp"

namespace FMOD
{
class Sound;
};

namespace red
{
class SoundResource : public IResource
{
public:
    RED_RESOURCE(ResourceType::SOUND);

    SoundResource(ResourceId resourceId);
    ~SoundResource();

    FMOD::Sound* GetSound();
    void SoundResource::SetSound(FMOD::Sound* sound);

private:
    FMOD::Sound* m_sound;
};
}  // namespace red
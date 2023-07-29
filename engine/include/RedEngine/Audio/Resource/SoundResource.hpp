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
    RED_RESOURCE(ResourceType::SOUND, L"sound");

    SoundResource(const Path& path);
    ~SoundResource();

    FMOD::Sound* GetSound();
    void SetSound(FMOD::Sound* sound);

private:
    FMOD::Sound* m_sound;
};
}  // namespace red
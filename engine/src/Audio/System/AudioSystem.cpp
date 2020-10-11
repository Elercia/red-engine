#include "RedEngine/Audio/System/AudioSystem.hpp"

namespace red
{

AudioSystem::AudioSystem(World* world) : System(world) {}

AudioSystem::~AudioSystem() = default;

void AudioSystem::Init() 
{ 
	FMOD::Studio::System::create(&systemFmod); 
}

void AudioSystem::Finalise() {}

void AudioSystem::Update() {}

}  // namespace red
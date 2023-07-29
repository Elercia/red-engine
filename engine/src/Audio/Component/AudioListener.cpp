#include "RedEngine/Audio/Component/AudioListener.hpp"

#include "RedEngine/Audio/AudioModule.hpp"

namespace red
{
AudioListener::AudioListener(Entity* owner) : Component(owner), m_listenerId(0), m_lastFramePos(0.f, 0.f)
{
}

AudioListener::~AudioListener()
{
}

}  // namespace red

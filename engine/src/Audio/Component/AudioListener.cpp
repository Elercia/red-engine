#include "RedEngine/Audio/AudioModule.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(AudioListener)

AudioListener::AudioListener(Entity* owner) : Component(owner), m_listenerId(0), m_lastFramePos(0.f, 0.f)
{
}

AudioListener::~AudioListener()
{
}

}  // namespace red

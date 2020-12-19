#include "RedEngine/Audio/Component/AudioListener.hpp"

namespace red
{
int AudioListener::s_listenerId = 0;

AudioListener::AudioListener(Entity* owner)
    : Component(owner), m_fmodVect(), m_listenerId(s_listenerId++)
{
}

AudioListener::~AudioListener() { s_listenerId--; }

}  // namespace red

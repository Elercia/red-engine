#pragma once

#include "fmod_common.h"

#include "RedEngine/Core/Entity/Components/Component.hpp"

namespace red
{
class AudioListener : public Component
{
    friend class AudioSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(AudioListener, Component)
    RED_END_COMPONENT_REGISTER()

    AudioListener(Entity* owner);
    ~AudioListener();

private:
    FMOD_VECTOR m_fmodVect;
    int m_listenerId;

    static int s_listenerId;
};

}  // namespace red
#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"

#include "fmod_common.h"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(AudioListener)

class AudioListener : public Component
{
    friend class AudioSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(AudioListener, Component)
    RED_END_COMPONENT_REGISTER()

    AudioListener(Entity* owner);
    ~AudioListener();

private:
    int m_listenerId;
    Vector2 m_lastFramePos;
};

}  // namespace red
#pragma once

#include "RedEngine/Core/Components/Component.hpp"

namespace red
{
class AudioListener : public Component
{
public:
    AudioListener(Entity* owner);
    ~AudioListener();
};

}  // namespace red
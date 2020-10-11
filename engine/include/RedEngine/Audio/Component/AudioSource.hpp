#pragma once

#include "RedEngine/Core/Components/Component.hpp"

namespace red
{
class AudioSource : public Component
{
public:
    AudioSource(Entity* owner);
    ~AudioSource();
};

}  // namespace red
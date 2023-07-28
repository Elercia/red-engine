#pragma once

#include "RedEngine/Input/UserInputDefinition.hpp"

namespace red
{
namespace utils
{
    class UserInputHelper
    {
    public:
        static UserActionMapping LoadActionMapping();

    private:
        static KeyMapping GetMappingFromConfigLine(const String& valueString);
        static ModifierKeyBitSet GetModifiersFromConfigLine(const String& modifierString);

        static KeyCodes::Enum GetKeyCode(const String& keyString);
    };
}  // namespace utils
}  // namespace red
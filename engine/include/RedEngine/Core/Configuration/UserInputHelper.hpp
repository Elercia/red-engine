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
        static KeyMapping GetMappingFromConfigLine(const std::string& valueString);
        static ModifierKeyBitSet GetModifiersFromConfigLine(const std::string& modifierString);

        static KeyCodes::Enum GetKeyCode(const std::string& keyString);
    };
}  // namespace utils
}  // namespace red
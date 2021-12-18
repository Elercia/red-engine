#pragma once

#include "RedEngine/Input/InputDefinition.hpp"


#include <array>
#include <bitset>
#include <map>
#include <variant>
#include <vector>

namespace red
{
struct ModifierKey
{
public:
    KeyCodes::Enum keyCode;

    enum Enum
    {
        LCTRL = 0,
        RCTRL,
        LALT,
        RALT,
        LSHIFT,
        RSHIFT,
    };
};

constexpr std::array<ModifierKey, 6> GetModifierKeyList()
{
    std::array<ModifierKey, 6> ar{};

    ar[ModifierKey::LCTRL] = {KeyCodes::KEY_LCTRL};
    ar[ModifierKey::RCTRL] = {KeyCodes::KEY_RCTRL};
    ar[ModifierKey::LALT] = {KeyCodes::KEY_LALT};
    ar[ModifierKey::RALT] = {KeyCodes::KEY_RALT};
    ar[ModifierKey::LSHIFT] = {KeyCodes::KEY_LSHIFT};
    ar[ModifierKey::RSHIFT] = {KeyCodes::KEY_RSHIFT};

    return ar;
}

constexpr std::array<ModifierKey, 6> g_modifierKeys = GetModifierKeyList();

using ModifierKeyBitSet = std::bitset<6>;

struct KeyMapping
{
    KeyCodes::Enum mapping{KeyCodes::MAX};
    ModifierKeyBitSet modifiers{};
};

using ActionKey = std::string;
using UserActionMapping = std::map<ActionKey, KeyMapping>;
using UserActionState = std::map<ActionKey, KeyState>;

using AxisKey = std::string;
}  // namespace red
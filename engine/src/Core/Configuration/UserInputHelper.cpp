#include "RedEngine/Core/Configuration/UserInputHelper.hpp"

#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Filesystem/Path.hpp"

#include <filesystem>
#include <string>

namespace red
{
namespace utils
{
    red::UserActionMapping UserInputHelper::LoadActionMapping()
    {
        Path p = Path::Resource(L"userInput.ini");
        auto iniConfig = utils::IniReader::ReadFromFile(p);

        UserActionMapping mappings{};

        for (auto& configLine : iniConfig)
        {
            // auto& cat = std::get<0>(configLine);
            auto& key = std::get<1>(configLine);
            auto& value = std::get<2>(configLine);

            KeyMapping mapping = GetMappingFromConfigLine(value);

            auto mappingIt = mappings.find(key);
            if (mappingIt != mappings.end())
            {
                RED_LOG_WARNING("Redefining key mapping for {}", key);
                mappingIt->second = mapping;
            }
            else
            {
                mappings.insert({key, mapping});
            }
        }

        return mappings;
    }

    red::KeyMapping UserInputHelper::GetMappingFromConfigLine(const std::string& valueString)
    {
        KeyMapping m;

        auto indexOfSemicolon = valueString.find_first_of(';');
        std::string keyString = valueString.substr(0, indexOfSemicolon);
        std::string modifierString = valueString.substr(indexOfSemicolon + 1, valueString.length());

        m.modifiers = GetModifiersFromConfigLine(modifierString);

        auto keyCode = GetKeyCode(keyString);

        if (keyCode == KeyCodes::MAX)
            RED_LOG_WARNING("Key mapping {} has a invalid key", keyString);

        m.mapping = keyCode;

        return m;
    }

    red::ModifierKeyBitSet UserInputHelper::GetModifiersFromConfigLine(const std::string& modifierString)
    {
        red::ModifierKeyBitSet modifiers;

        if (modifierString.find("lctrl+") != std::string::npos)
        {
            modifiers.set(ModifierKey::LCTRL);
        }
        if (modifierString.find("rctrl+") != std::string::npos)
        {
            modifiers.set(ModifierKey::RCTRL);
        }

        if (modifierString.find("lalt+") != std::string::npos)
        {
            modifiers.set(ModifierKey::LALT);
        }
        if (modifierString.find("ralt+") != std::string::npos)
        {
            modifiers.set(ModifierKey::RALT);
        }

        if (modifierString.find("lshift+") != std::string::npos)
        {
            modifiers.set(ModifierKey::LSHIFT);
        }
        if (modifierString.find("rshift+") != std::string::npos)
        {
            modifiers.set(ModifierKey::RSHIFT);
        }

        return modifiers;
    }

    red::KeyCodes::Enum UserInputHelper::GetKeyCode(const std::string& keyString)
    {
        auto codes = GetKeyCodeReadableDb();

        for (size_t i = 0; i < codes.size(); i++)
        {
            auto& readable = codes[i];
            if (keyString == readable)
            {
                return static_cast<red::KeyCodes::Enum>(i);
            }
        }

        return KeyCodes::MAX;
    }

}  // namespace utils
}  // namespace red
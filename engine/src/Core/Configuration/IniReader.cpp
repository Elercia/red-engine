#include "RedEngine/Core/Configuration/IniReader.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#include <fstream>

namespace red
{
namespace utils
{
    Array<iniCatKeyValue> IniReader::ReadFromFile(const Path& path)
    {
        namespace fs = std::filesystem;

        std::ifstream stream;

        stream.open(path.GetAscciiPath());

        if (!path.Exist() || path.IsDirectory() || !stream.is_open())
        {
            RED_LOG_WARNING("IniReader cannot load file {} because it doesn't exists", path.GetAscciiPath());
            return {};
        }

        Array<iniCatKeyValue> iniKeyCatValues;

        String lineBuffer;
        String currentCategory = "default";

        while (std::getline(stream, lineBuffer))
        {
            utils::Trim(lineBuffer);

            if (lineBuffer[0] == '#' || lineBuffer[0] == ';' || lineBuffer.empty())
                continue;

            if (lineBuffer[0] == '[')
            {
                // start of a new category
                auto endChar = lineBuffer.find_first_of(']');
                if (endChar == String::npos)
                {
                    RED_LOG_WARNING("IniReader invalid category : {}", lineBuffer);
                    continue;
                }

                currentCategory = lineBuffer.substr(1, endChar - 1);
                utils::Trim(currentCategory);

                continue;
            }

            // new key = value pair
            auto values = utils::Split(lineBuffer, '=');
            if (values.size() != 2)
            {
                RED_LOG_WARNING("IniReader invalid line : {}", lineBuffer);
                continue;
            }

            auto& key = utils::Trim(values[0]);
            auto value = utils::Trim(values[1]);

            iniKeyCatValues.push_back(std::make_tuple(currentCategory, key, value));
        }

        return iniKeyCatValues;
    }
}  // namespace utils
}  // namespace red

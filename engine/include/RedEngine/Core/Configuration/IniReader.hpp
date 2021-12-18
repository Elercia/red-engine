#pragma once

#include "RedEngine/Filesystem/Path.hpp"


#include <string>
#include <tuple>
#include <vector>

namespace red
{
namespace utils
{
    // <category, key, value>
    using iniCatKeyValue = std::tuple<std::string, std::string, std::string>;

    class IniReader
    {
    public:
        [[nodiscard]] static std::vector<iniCatKeyValue> ReadFromFile(const Path& path);

    private:
        IniReader();
    };
}  // namespace utils
}  // namespace red
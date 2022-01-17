#pragma once

#include "RedEngine/Filesystem/Path.hpp"

#include <string>
#include <tuple>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
namespace utils
{
    // <category, key, value>
    using iniCatKeyValue = std::tuple<std::string, std::string, std::string>;

    class IniReader
    {
    public:
        [[nodiscard]] static Array<iniCatKeyValue> ReadFromFile(const Path& path);

    private:
        IniReader();
    };
}  // namespace utils
}  // namespace red
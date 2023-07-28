#pragma once

#include "RedEngine/Filesystem/Path.hpp"

#include "RedEngine/Core/Container/String.hpp"
#include <tuple>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
namespace utils
{
    // <category, key, value>
    using iniCatKeyValue = std::tuple<String, String, String>;

    class IniReader
    {
    public:
        [[nodiscard]] static Array<iniCatKeyValue> ReadFromFile(const Path& path);

    private:
        IniReader();
    };
}  // namespace utils
}  // namespace red
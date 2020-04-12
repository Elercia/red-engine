#pragma once

#include <string>
#include <tuple>
#include <filesystem>
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
        static std::vector<iniCatKeyValue> ReadFromFile(std::filesystem::path path);

    private:
        IniReader();
    };
}  // namespace utils
}  // namespace red
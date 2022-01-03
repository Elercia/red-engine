#pragma once

#include <string>
#include <vector>

namespace red
{
namespace utils
{
    std::string& Trim(std::string& str);

    std::vector<std::string> Split(const std::string& str, char delim);

    std::wstring ToUnicodeString(const std::string_view str);

    void ToUpperCase(std::string& str);
    void ToUpperCase(std::wstring& str);
}  // namespace utils
}  // namespace red

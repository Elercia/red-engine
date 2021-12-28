#include "RedEngine/Utils/UtilityModule.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#include <algorithm>
#include <sstream>

namespace red::utils
{
std::string& Trim(std::string& str)
{
    if (str.empty())
        return str;

    size_t start = 0;
    auto end = str.length();

    while (start < end && std::isspace(str[start]) != 0)
    {
        start++;
    }

    while (end > 0 && std::isspace(str[end - 1]) != 0)
    {
        end--;
    }

    str = str.substr(start, end - start);

    return str;
}

std::vector<std::string> Split(const std::string& str, const char delim)
{
    std::string tmp;
    std::stringstream stream;
    std::vector<std::string> ret;

    stream << str;
    while (std::getline(stream, tmp, delim))
    {
        ret.push_back(tmp);
    }

    return ret;
}

std::wstring ToUnicodeString(const std::string_view str)
{
    if (str.empty())
        return L"";

    std::wstring unicodeStr(str.size(), L'#');
    mbstowcs(&unicodeStr[0], &(str.front()), str.size());

    return unicodeStr;
}

void ToUpperCase(std::string& str)
{
    std::for_each(str.begin(), str.end(), [](char& c) { c = (char) std::toupper(c); });
}

void ToUpperCase(std::wstring& str)
{
    std::for_each(str.begin(), str.end(), [](wchar_t& c) { c = (char) std::toupper(c); });
}

}  // namespace red::utils
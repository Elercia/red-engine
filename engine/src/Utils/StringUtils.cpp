#include "RedEngine/Utils/StringUtils.hpp"

#include <sstream>

namespace red::utils
{
std::string& Trim(std::string& str)
{
    if (str.empty())
        return str;

    int start = 0;
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
}  // namespace red::utils
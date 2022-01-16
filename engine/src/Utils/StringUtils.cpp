#include "RedEngine/Utils/StringUtils.hpp"

#include "RedEngine/Utils/UtilityModule.hpp"

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

namespace StringParser
{
    bool Expect(const char** it, const char* end, char c)
    {
        if (*it == end)
            return false;

        if (**it != c)
            return false;

        (*it)++;

        return true;
    }

    bool ReadFloat(const char** it, const char* end, float& f)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        float value = strtof(*it, &endptr);

        if (endptr == *it)
            return false;

        f = value;
        *it = endptr;

        return true;
    }

    bool ReadDouble(const char** it, const char* end, double& f)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        double value = strtod(*it, &endptr);

        if (endptr == *it)
            return false;

        f = value;
        *it = endptr;

        return true;
    }

    bool ReadInt(const char** it, const char* end, int& i)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        int value = strtol(*it, &endptr, 10);

        if (endptr == *it)
            return false;

        i = value;
        *it = endptr;

        return true;
    }

    bool ReadLong(const char** it, const char* end, int64& i)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        int64 value = strtol(*it, &endptr, 10);

        if (endptr == *it)
            return false;

        i = value;
        *it = endptr;

        return true;
    }

    bool ReadUnsignedInt(const char** it, const char* end, uint32& i)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        uint32 value = strtoul(*it, &endptr, 10);

        if (endptr == *it)
            return false;

        i = value;
        *it = endptr;

        return true;
    }

    bool ReadUnsignedLong(const char** it, const char* end, uint64& i)
    {
        if (*it == end)
            return false;

        char* endptr = nullptr;
        uint64 value = strtoul(*it, &endptr, 10);

        if (endptr == *it)
            return false;

        i = value;
        *it = endptr;

        return true;
    }

};  // namespace StringParser

}  // namespace red::utils
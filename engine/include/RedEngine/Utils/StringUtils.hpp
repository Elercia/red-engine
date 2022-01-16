#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <string>
#include <string_view>
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

    namespace StringParser
    {
        bool Expect(const char** it, const char* end, char c);
        bool ReadFloat(const char** it, const char* end, float& f);
        bool ReadDouble(const char** it, const char* end, double& f);
        bool ReadInt(const char** it, const char* end, int& i);
        bool ReadLong(const char** it, const char* end, int64& i);
        bool ReadUnsignedInt(const char** it, const char* end, uint32& i);
        bool ReadUnsignedLong(const char** it, const char* end, uint64& i);
    };  // namespace StringParser
}  // namespace utils
}  // namespace red

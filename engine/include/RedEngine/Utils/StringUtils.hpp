#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <string>
#include <string_view>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
namespace utils
{
    std::string& Trim(std::string& str);

    Array<std::string> Split(const std::string& str, char delim);

    std::wstring ToUnicodeString(const std::string_view str);

    void ToLowerCase(std::string& str);
    void ToLowerCase(std::wstring& str);

    void ToUpperCase(std::string& str);
    void ToUpperCase(std::wstring& str);

    std::string::size_type Find(const std::string_view& in, const std::string_view& toFind, bool caseInsensitive = false);

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

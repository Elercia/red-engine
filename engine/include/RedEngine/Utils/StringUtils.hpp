#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/String.hpp"
#include "RedEngine/Utils/Types.hpp"

namespace red
{
namespace utils
{
    String& Trim(String& str);

    Array<String> Split(const String& str, char delim);

    std::wstring ToUnicodeString(const StringView str);

    void ToLowerCase(String& str);
    void ToLowerCase(std::wstring& str);

    void ToUpperCase(String& str);
    void ToUpperCase(std::wstring& str);

    String::size_type Find(const StringView& in, const StringView& toFind, bool caseInsensitive = false);

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

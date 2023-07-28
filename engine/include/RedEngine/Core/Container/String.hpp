#pragma once

namespace red
{
template <typename CharType>
class BasicString
{
public:
    using size_type = uint32;
    using value_type = CharType;
    static constexpr size_type npos = (uint32) -1;

    constexpr BasicString();
    constexpr BasicString(const BasicString& other);
    constexpr BasicString(BasicString&& other);

    constexpr BasicString& operator=(const BasicString& other);
    constexpr BasicString& operator=(BasicString&& other);

    // Implicits operators & ctors
    constexpr BasicString& operator=(const CharType* cstr);
    constexpr BasicString(const CharType* cstr);

    constexpr bool empty() const;
    constexpr size_type length() const;
    constexpr size_type size() const;

    CharType& at(size_type index);
    constexpr CharType at(size_type index) const;

    constexpr BasicString<CharType> substr(size_type pos = 0, size_type count = npos) const;
    constexpr size_type find_last_of(CharType ch, size_type pos = npos) const;

    constexpr CharType* c_str() const;
};

template <typename CharType>
class BasicStringView
{
public:
    using size_type = BasicString<CharType>::size_type;
    static constexpr size_type npos = (uint32) -1;

    constexpr BasicStringView();
    constexpr BasicStringView(const BasicStringView& other);
    constexpr BasicStringView(BasicStringView&& other);

    constexpr BasicStringView& operator=(const BasicStringView& other);
    constexpr BasicStringView& operator=(BasicStringView&& other);

    // Implicits operators & ctors
    constexpr BasicStringView& operator=(const CharType* cstr);
    constexpr BasicStringView(const CharType* cstr);

    constexpr BasicStringView& operator=(const BasicString<CharType>& cstr);
    constexpr BasicStringView(const BasicString<CharType>& cstr);

    constexpr bool empty() const;
    constexpr size_type length() const;
    constexpr size_type size() const;

    CharType& at(size_type index);
    constexpr CharType at(size_type index) const;

    constexpr BasicStringView<CharType> substr(size_type pos = 0, size_type count = npos) const;
    constexpr size_type find_last_of(CharType ch, size_type pos = npos) const;
};

using String = BasicString<char>;
using WString = BasicString<wchar_t>;

using StringView = BasicStringView<char>;
using WStringView = BasicStringView<wchar_t>;
}  // namespace red

#include "inl/String.inl"
#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <string_view>
#include <string>

namespace red
{
// Representation of a path
// Can be build using static methods from the game resources or from the user game path (usually MyDocuments or ~
// followed by the game name) The path status is refreshed on creation but can be refresh at anytime
class Path
{
public:
    // API to construct a path inside the user directory
    static Path User(const std::wstring& path);
    // API to construct a path inside the game resources
    static Path Resource(const std::wstring& path);

    // c-string like creators
    static Path Resource(const std::string& path);
    static Path User(const std::string& path);

private:
    static std::wstring GetUserBasePath();
    static std::wstring GetResourceBasePath();

public:
    ~Path();

    std::wstring_view GetPath() const;
    std::string GetAscciiPath() const;

    bool Exist() const;
    bool IsDirectory() const;
    bool IsFile() const;

    uint64 GetHash() const;

    Path& Append(const std::wstring& str);

    void ForceRefreshStatus();  // Force the refresh of the path

private:
    explicit Path(std::wstring path);
    void SetUnicodePath(const std::wstring& unicodeStr);

private:
    enum PathState
    {
        VALID = 1 << 0,      // The Path is a valid physical path or a valid virtual path (doesn't guarantee existence)
        EXIST = 1 << 3,      // The path exist on the disk
        TYPE_FILE = 1 << 4,  // 1 => file, 0 => directory (folder). Invalid if not exist
    };
    using PathStates = uint32;

private:
    std::wstring m_unicodePath;
    PathStates m_states;
    uint32 m_hash;
};
}  // namespace red

namespace std
{
template <>
struct less<red::Path>
{
    bool operator()(const red::Path& lhs, const red::Path& rhs) const
    {
        return lhs.GetHash() < rhs.GetHash();
    }
};
}  // namespace std
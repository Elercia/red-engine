#include "RedEngine/Filesystem/Path.hpp"

#include "RedEngine/Filesystem/FileSystemModule.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Math/Hash.hpp"
#include "RedEngine/Utils/BitfieldUtils.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#if defined(RED_WINDOWS)
#include <shlobj.h>
#include <windows.h>
#endif

#include <algorithm>
#include <filesystem>

namespace red
{
std::wstring Path::GetUserBasePath()
{
#if defined(RED_WINDOWS)
    WCHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents);

    RedAssert(result == S_OK, "failed to get patht to MyDocuments folder");

    std::wstring unicodeStr(my_documents);

#elif defined(RED_LINUX)
    std::wstring unicodeStr = L"~";
#endif

    return unicodeStr + L"/" + utils::ToUnicodeString(Engine::GetInstance()->GetGameName());
}

std::wstring Path::GetResourceBasePath()
{
    return L"./resources/";
}

Path::Path() : m_states(0), m_hash((uint32) -1)
{
}

Path Path::User(const std::wstring& path)
{
    return Path(GetUserBasePath() + path);
}

Path Path::User(const std::string& path)
{
    return User(utils::ToUnicodeString(path));
}

Path Path::Resource(const std::wstring& path)
{
    return Path(GetResourceBasePath() + path);
}

Path Path::Resource(const std::string& path)
{
    return Resource(utils::ToUnicodeString(path));
}

Path::Path(std::wstring path) : m_unicodePath(), m_states(0)
{
    SetUnicodePath(std::move(path));
    ForceRefreshStatus();
}

void Path::SetUnicodePath(const std::wstring& unicodeStr)
{
    // All path are to upper cases
    m_unicodePath = unicodeStr;
    utils::ToUpperCase(m_unicodePath);
}

Path::~Path()
{
}

std::wstring_view Path::GetPath() const
{
    return m_unicodePath;
}

std::string Path::GetAscciiPath() const
{
    std::string str;
    std::transform(m_unicodePath.begin(), m_unicodePath.end(), std::back_inserter(str),
                   [](wchar_t c) { return (char) c; });

    return str;
}

bool Path::Exist() const
{
    return HasBit(m_states, PathState::VALID) && HasBit(m_states, PathState::EXIST);
}

bool Path::IsDirectory() const
{
    return Exist() && HasBit(m_states, PathState::TYPE_FILE) == false;
}

bool Path::IsFile() const
{
    return Exist() && HasBit(m_states, PathState::TYPE_FILE);
}

uint64 Path::GetHash() const
{
    return m_hash;
}

Path& Path::Append(const std::wstring& str)
{
    SetUnicodePath(m_unicodePath += str);
    ForceRefreshStatus();

    return *this;
}

void Path::ForceRefreshStatus()
{
    m_hash = wfnv1a32(m_unicodePath);

    namespace fs = std::filesystem;

    fs::path internalPath(m_unicodePath);

    m_states = 0;

    bool exist = fs::exists(internalPath);

    if (exist)
        SetBit(m_states, PathState::EXIST);

    if (fs::is_regular_file(internalPath))
        SetBit(m_states, PathState::TYPE_FILE);

    if (exist && (fs::status_known(fs::status(internalPath)) || fs::is_regular_file(internalPath) ||
                  fs::is_directory(internalPath) || fs::is_symlink(internalPath)))
    {
        SetBit(m_states, PathState::VALID);
    }
    else if (!exist)
    {
        SetBit(m_states, PathState::VALID);
    }
}

bool Path::operator==(const Path& other) const
{
    return m_hash == other.m_hash;   
}

bool Path::operator!=(const Path& other) const
{
    return !(*this == other);
}

template<>
uint64 Hash(const Path& value)
{
    return value.GetHash();
}

}  // namespace red

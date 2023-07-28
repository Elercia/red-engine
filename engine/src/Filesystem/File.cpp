#include "RedEngine/Filesystem/File.hpp"

#include "RedEngine/Filesystem/FileSystemModule.hpp"

#include "RedEngine/Utils/BitfieldUtils.hpp"

#include <filesystem>

using namespace std::filesystem;

namespace red
{
File::File(const Path& path, OpenModes openMode) : m_openModes(openMode), m_path(path), m_file(nullptr)
{
}

File::~File()
{
    if (IsOpen())
        Close();
}

bool File::Open()
{
    if (!m_path.IsFile() && (!m_path.Exist() && !HasBit(m_openModes, OpenMode::CREATE)))
        return false;

    String openModeStr;
    if ((HasBit(m_openModes, OpenMode::READ) && HasBit(m_openModes, OpenMode::WRITE)) ||
        HasBit(m_openModes, OpenMode::TRUNCATE))
    {
        if (HasBit(m_openModes, OpenMode::CREATE) || HasBit(m_openModes, OpenMode::TRUNCATE))
            openModeStr += "w+";
        else if (HasBit(m_openModes, OpenMode::APPEND))
            openModeStr += "a+";
        else
            openModeStr += "r+";
    }
    else
    {
        if (HasBit(m_openModes, OpenMode::READ))
            openModeStr += "r";
        if (HasBit(m_openModes, OpenMode::WRITE))
            openModeStr += "w";
        if (HasBit(m_openModes, OpenMode::APPEND))
            openModeStr += "a";
    }

    if (HasBit(m_openModes, OpenMode::BINARY))
        openModeStr += "b";

    const auto fileStr = m_path.GetAscciiPath();
    if (HasBit(m_openModes, OpenMode::CREATE))
    {
        const auto fsPath = path(fileStr).remove_filename();
        create_directories(fsPath);
    }

    m_file = fopen(fileStr.c_str(), openModeStr.c_str());

    if (m_file == nullptr)
        return false;

    return true;
}

bool File::Close()
{
    int ret = 0;
    if (m_file != nullptr)
        ret = fclose(m_file);

    m_file = nullptr;

    return ret == 0;
}

bool File::IsOpen() const
{
    return m_file != nullptr;
}

bool File::Write(const String& str)
{
    if (m_file == nullptr)
        return false;

    if (!HasBit(m_openModes, OpenMode::WRITE))
        return false;

    const int ret = fputs(str.c_str(), m_file);

    return ret != EOF;
}

bool File::Write(const uint8* data, sizet size)
{
    if (m_file == nullptr)
        return false;

    if (!HasBit(m_openModes, OpenMode::WRITE))
        return false;

    const sizet ret = fwrite(data, sizeof(uint8), size, m_file);

    return ret == size;
}

sizet File::Size()
{
    if (m_file == nullptr)
        return 0;

    const auto currentPos = ftell(m_file);
    fseek(m_file, 0L, SEEK_END);
    auto size = ftell(m_file);
    fseek(m_file, currentPos, SEEK_SET);

    return size;
}

}  // namespace red

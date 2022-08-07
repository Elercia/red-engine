#pragma once

#include "Path.hpp"

namespace red
{
enum OpenMode
{
    READ = 1 << 0,
    WRITE = 1 << 1,   // write at the start
    APPEND = 1 << 2,  // write at the end
    BINARY = 1 << 3,
    TRUNCATE = 1 << 4,  // truncate file content on open
    CREATE = 1 << 5,    // Create on open

    READ_WRITE = READ | WRITE,
    READ_WRITE_BIN = READ | WRITE | BINARY,
    READ_WRITE_TC = READ | WRITE | TRUNCATE | CREATE,
};
using OpenModes = uint32;

class File
{
public:
    explicit File(const Path& path, OpenModes openMode);
    ~File();

    bool Open();
    bool Close();

    bool IsOpen() const;

    bool Write(const std::string& str);
    bool Write(const uint8* data, sizet size);

    sizet Size();  // file size in bytes

private:
    OpenModes m_openModes;
    Path m_path;
    FILE* m_file;
};

}  // namespace red

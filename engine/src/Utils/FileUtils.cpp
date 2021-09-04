#include "RedEngine/Utils/FileUtils.hpp"

#include <fstream>
#include <sstream>

std::string red::ReadFile(const Path& fullPath)
{
    std::wifstream in;
    in.open(fullPath.GetPath().data());

    if (!in.is_open())
        return "";

    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

#include "RedEngine/Utils/FileUtils.hpp"

#include <fstream>
#include <sstream>

std::string red::ReadFile(const std::string& fullPath)
{
    std::ifstream in;
    in.open(fullPath);

    if (!in.is_open())
        return "";

    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

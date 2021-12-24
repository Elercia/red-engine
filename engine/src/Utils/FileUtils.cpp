#include "RedEngine/Utils/UtilsModule.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <fstream>
#include <sstream>

namespace red
{
std::string ReadFile(const Path& fullPath)
{
    std::ifstream in;
    std::string asciiString = fullPath.GetAscciiPath();

    in.open(asciiString);

    if (!in.is_open())
        return "";

    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
}  // namespace red

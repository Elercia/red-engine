#include "RedEngine/Utils/FileUtils.hpp"

#include "RedEngine/Utils/UtilityModule.hpp"

#include <fstream>
#include <sstream>

namespace red
{
String ReadFile(const Path& fullPath)
{
    std::ifstream in;
    String asciiString = fullPath.GetAscciiPath();

    in.open(asciiString);

    if (!in.is_open())
        return "";

    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
}  // namespace red

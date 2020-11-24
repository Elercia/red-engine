#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <string>
#include <vector>

namespace red
{
namespace utils
{
    std::string& Trim(std::string& str);

    std::vector<std::string> Split(const std::string& str, char delim);
}  // namespace utils
}  // namespace red

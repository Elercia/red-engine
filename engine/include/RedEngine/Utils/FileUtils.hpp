#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Filesystem/Path.hpp"

namespace red
{
std::string ReadFile(const Path& fullPath);
}
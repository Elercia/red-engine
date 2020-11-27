#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <string>
//TODO Add filesystem path separator
namespace red
{
std::string ReadFile(const std::string& fullPath);
}
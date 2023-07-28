#pragma once

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
class ICVar;

class CVarUtils
{
public:
    static String GetLongName(const String& category, const String& key);
    static String GetLongName(const ICVar* cvar);

private:
    CVarUtils() = delete;
    ~CVarUtils() = delete;
};
}  // namespace red

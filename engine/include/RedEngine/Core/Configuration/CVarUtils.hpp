#pragma once

#include <string>

namespace red
{
class ICVar;

class CVarUtils
{
public:
    static std::string GetLongName(const std::string& category, const std::string& key);
    static std::string GetLongName(const ICVar* cvar);

private:
    CVarUtils() = delete;
    ~CVarUtils() = delete;
};
}  // namespace red

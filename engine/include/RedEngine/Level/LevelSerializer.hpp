#pragma once

#include <string>

namespace red
{
class Level;

class ILevelSerializer
{
public:
    explicit ILevelSerializer(Level* level);

    virtual bool SerializeToFile(const std::string& path) = 0;
    virtual bool DeserializeFromFile(const std::string& path) = 0;

protected:
    Level* m_level;
};
}  // namespace red
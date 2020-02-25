#pragma once

#include <map>
#include <string>

namespace red
{
using ConfigurationValue = union {
    bool dataBool;
    std::string dataString;
    float dataFloat;
    int dataInt;
};

class Configuration
{
public:
    Configuration();
    explicit Configuration(std::string configFilePath);
    ~Configuration();

    void InitFromCommandLine(int argc, char* argv[]);

    template <typename T>
    T Get(std::string name, T defaultValue);

    template <typename T>
    void Set(std::string name, T value);

private:
    std::map<std::string, std::string> m_configs;
};

}  // namespace red

#include "inl/Configuration.inl"
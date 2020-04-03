#pragma once

#include <unordered_map>
#include <string>

namespace red
{
class ICVar;

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void ParseCommandLine(int argc, char* argv[]);

    void RegisterNewConfigVariable(ICVar* configVariable);

    template <typename T>
    void ChangeVar(std::string name, std::string category, T value)
    {
        auto it = m_configVariable.find(category + "_" + name);

        if (it == m_configVariable.end())
        {
            return;
        }

        auto casted = static_cast<CVar<T>*>(it->second);

        casted->ChangeValue(value);
    }

    static void NewCVar(ICVar* configVariable);

    static Configuration& GetInstance();

private:
    std::unordered_map<std::string, ICVar*> m_configVariable;
};

}  // namespace red
#include <nlohmann/json.hpp>

#include "RedEngine/Core/Debug/DebugMacros.hpp"

namespace red
{
/*template <typename T>
std::string Serialize(const T& value)
{
    RedError("Hiting a Serialize function that is not implemented");
    return "not-implemented";
}

template <typename T>
bool Deserialize(T& value, const std::string& str)
{
    RedError("Hiting a Deserialize function that is not implemented");
    return false;
}*/

/*template <>
template <typename T>
std::string Serialize(const Array<T>& value)
{
    using json = nlohmann::json;
    json arrayData;

    for (auto& elem : value)
    {
        arrayData.push_back(Serialize(elem));
    }

    return arrayData.dump();
}

template <>
template <typename T>
bool Deserialize(Array<T>& value, const std::string& str)
{
    using json = nlohmann::json;
    json arrayData = json::parse(str);

    for (auto& elem : arrayData)
    {
        T elemValue;
        Deserialize(elemValue, elem);
        value.push_back(elemValue);
    }

    return true;
}*/
}  // namespace red
#include <nlohmann/json.hpp>

#include "RedEngine/Core/Debug/DebugMacros.hpp"

namespace red
{
/*template <typename T>
String Serialize(const T& value)
{
    RedError("Hiting a Serialize function that is not implemented");
    return "not-implemented";
}

template <typename T>
bool Deserialize(T& value, const String& str)
{
    RedError("Hiting a Deserialize function that is not implemented");
    return false;
}*/

/*template <>
template <typename T>
String Serialize(const Array<T>& value)
{
    using json = Json;
    json arrayData;

    for (auto& elem : value)
    {
        arrayData.push_back(Serialize(elem));
    }

    return arrayData.dump();
}

template <>
template <typename T>
bool Deserialize(Array<T>& value, const String& str)
{
    using json = Json;
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
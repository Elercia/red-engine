
#include <nlohmann/json.hpp>

namespace red
{
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
}
}  // namespace red
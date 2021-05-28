#include "RedEngine/Math/Vector.hpp"

#include <string>

namespace red
{
std::string Serialize(const Vector2& value);
bool Deserialize(Vector2& value, const std::string& str);
}  // namespace red
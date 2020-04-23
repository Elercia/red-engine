
namespace red
{
constexpr double Mathf::Clamp(double value, double min, double max)
{
    return Max(min, Min(max, value));
}
constexpr float Mathf::Clamp(float value, float min, float max)
{
    return Max(min, Min(max, value));
}

constexpr double Mathf::Min(double l, double r) { return l < r ? l : r; }
constexpr double Mathf::Max(double l, double r) { return l > r ? l : r; }

constexpr float Mathf::Min(float l, float r) { return l < r ? l : r; }
constexpr float Mathf::Max(float l, float r) { return l > r ? l : r; }

constexpr float Mathf::Clamp01(float value) { return Clamp(value, 0.F, 1.F); }
constexpr double Mathf::Clamp01(double value) { return Clamp(value, 0., 1.); }

}  // namespace red
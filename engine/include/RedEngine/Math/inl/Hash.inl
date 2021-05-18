namespace red
{
constexpr uint32 fnv1a32(const std::string_view& s)
{
    return fnv1a32(s, s.length() - 1);
}

// FNV-1a 32bit hashing algorithm from https://gist.github.com/Lee-R/3839813
constexpr uint32 fnv1a32(const std::string_view& s, sizet count)
{
    return ((count > 0 ? fnv1a32(s, count - 1) : 2166136261u) ^ s.at(count)) * 16777619u;
}
}  // namespace red
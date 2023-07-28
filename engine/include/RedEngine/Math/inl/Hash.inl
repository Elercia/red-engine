namespace red
{
template <typename T>
uint64 Hash(const T& value)
{
    return Hash<uint64>((uint64) value);
}
    
constexpr uint32 fnv1a32(const StringView& s)
{
    return fnv1a32(s, s.length() - 1);
}

// FNV-1a 32bit hashing algorithm from https://gist.github.com/Lee-R/3839813
constexpr uint32 fnv1a32(const StringView& s, StringView::size_type count)
{
    return ((count > 0 ? fnv1a32(s, count - 1) : 2166136261u) ^ s.at(count)) * 16777619u;
}

constexpr uint32 wfnv1a32(const WStringView& s)
{
    return wfnv1a32(s, s.length() - 1);
}

constexpr uint32 wfnv1a32(const WStringView& s, WStringView::size_type count)
{
    return ((count > 0 ? wfnv1a32(s, count - 1) : 2166136261u) ^ s.at(count)) * 16777619u;
}
}  // namespace red
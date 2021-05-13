namespace red
{
template <typename T>
constexpr TypeTraits TypeInfo()
{
    constexpr std::string_view full_name{RED_FUNCNAME};
    constexpr std::string_view left_marker{RED_FUNCNAME_START};
    constexpr std::string_view right_marker{RED_FUNCNAME_END};
    
    constexpr auto left_marker_index = full_name.find(left_marker);
    static_assert(left_marker_index != std::string_view::npos, "Type T is not starting with left_marker");

    constexpr auto start_index = left_marker_index + left_marker.size();

    constexpr auto end_index = full_name.find(right_marker, left_marker_index);
    static_assert(end_index != std::string_view::npos, "Type T is not ending with right_marker");

    constexpr auto length = end_index - start_index;
    
    std::string_view typeName = full_name.substr(start_index, length);

    //const char* typeName = full_name.substr(0, full_name.length()).data();

    TypeTraits typeTraits{typeName, 0};

    return typeTraits;
}
}  // namespace red
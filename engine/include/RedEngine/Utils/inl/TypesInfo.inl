namespace red
{
template <typename T>
constexpr TypeTraits TypeInfo()
{
    constexpr std::string_view full_name{RED_FUNCNAME};
    constexpr std::string_view left_marker{RED_FUNCNAME_START};
    constexpr std::string_view right_marker{RED_FUNCNAME_END};
    constexpr std::string_view function_struct_start{RED_FUNCNAME_STRUCT_START};
    constexpr std::string_view function_class_start{RED_FUNCNAME_CLASS_START};

    constexpr auto left_marker_index = full_name.find(left_marker);
    static_assert(left_marker_index != std::string_view::npos, "Type T is not starting with left_marker");

    constexpr auto start_index = left_marker_index + left_marker.size();

    constexpr auto end_index = full_name.find(right_marker, left_marker_index);
    static_assert(end_index != std::string_view::npos, "Type T is not ending with right_marker");

    constexpr auto length = end_index - start_index;

    constexpr auto typeName = full_name.substr(start_index, length);

    constexpr auto structSlicedTypeName = function_struct_start.empty() == false && typeName.find(function_struct_start) != std::string_view::npos
                                              ? typeName.substr(function_struct_start.length())
                                              : typeName;

    constexpr auto classSlicedTypeName = function_class_start.empty() == false && structSlicedTypeName.find(function_class_start) != std::string_view::npos
                                             ? structSlicedTypeName.substr(function_class_start.length())
                                             : structSlicedTypeName;

    constexpr auto hash = fnv1a32(classSlicedTypeName);

    constexpr TypeTraits typeTraits{classSlicedTypeName, hash};

    return typeTraits;
}
}  // namespace red
namespace red
{
template <typename IResourceType>
ResourceLoader<IResourceType>::ResourceLoader(const std::string& name, ResourceType resourceType)
    : IResourceLoader(name, resourceType)
{
}
}  // namespace red
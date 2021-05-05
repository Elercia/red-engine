namespace red
{
template <typename IResourceType>
ResourceLoader<IResourceType>::ResourceLoader(ResourceType resourceType, World* world)
    : IResourceLoader(resourceType, world)
{
}

template <typename IResourceType>
std::shared_ptr<IResourceType> ResourceLoader<IResourceType>::GetFromCache(const std::string& name)
{
    auto it = m_loadedResources.find(name);

    if (it != m_loadedResources.end())
    {
        return it->second;
    }

    return nullptr;
}

template <typename IResourceType>
std::shared_ptr<IResourceType> ResourceLoader<IResourceType>::GetOrCreateFromCache(const std::string& name)
{
    auto ptr = GetFromCache(name);

    if (ptr)
        return ptr;

    ptr = std::make_shared<IResourceType>(name);

    m_loadedResources.insert({name, ptr});

    return ptr;
}
}  // namespace red
namespace red
{
template <typename Type>
ResourceLoader<Type>::ResourceLoader(ResourceType resourceType, World* world) : IResourceLoader(resourceType, world)
{
}

template <typename Type>
std::shared_ptr<Type> ResourceLoader<Type>::GetFromCache(const Path& path)
{
    auto it = m_loadedResources.find(path);

    if (it != m_loadedResources.end())
    {
        return it->second;
    }

    return nullptr;
}

template <typename Type>
std::shared_ptr<Type> ResourceLoader<Type>::GetOrCreateFromCache(const Path& path)
{
    auto ptr = GetFromCache(path);

    if (ptr)
        return ptr;

    ptr = std::make_shared<Type>(path);

    m_loadedResources.insert({path, ptr});

    return ptr;
}

template <typename Type>
void ResourceLoader<Type>::FreeUnusedResources()
{
    for (auto resourceIt = m_loadedResources.begin(); resourceIt != m_loadedResources.end();)
    {
        auto& resource = resourceIt->second;

        if (resource.use_count() == 1)
        {
            FreeResource(resource);

            resourceIt = m_loadedResources.erase(resourceIt);
        }

        resourceIt++;
    }
}

template <typename Type>
void ResourceLoader<Type>::FreeAllResources()
{
    for (auto resourceIt = m_loadedResources.begin(); resourceIt != m_loadedResources.end(); resourceIt++)
    {
        auto& resource = resourceIt->second;

        FreeResource(resource);
    }
}

template <typename Type>
std::shared_ptr<red::IResource> red::ResourceLoader<Type>::LoadAbstractResource(const Path& path)
{
    return LoadResource(path);
}

}  // namespace red
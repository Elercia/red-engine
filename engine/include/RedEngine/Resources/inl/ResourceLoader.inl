namespace red
{
template <typename Type>
ResourceLoader<Type>::ResourceLoader(ResourceType resourceType, World* world) : IResourceLoader(resourceType, world)
{
}

template <typename Type>
std::shared_ptr<Type> ResourceLoader<Type>::GetFromCache(const std::string& name)
{
    auto it = m_loadedResources.find(name);

    if (it != m_loadedResources.end())
    {
        return it->second;
    }

    return nullptr;
}

template <typename Type>
std::shared_ptr<Type> ResourceLoader<Type>::GetOrCreateFromCache(const std::string& name)
{
    auto ptr = GetFromCache(name);

    if (ptr)
        return ptr;

    ptr = std::make_shared<Type>(name);

    m_loadedResources.insert({name, ptr});

    return ptr;
}

template <typename Type>
void red::ResourceLoader<Type>::FreeUnusedResources()
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
void red::ResourceLoader<Type>::FreeAllResources()
{
    for (auto resourceIt = m_loadedResources.begin(); resourceIt != m_loadedResources.end(); resourceIt++)
    {
        auto& resource = resourceIt->second;

        FreeResource(resource);
    }
}

}  // namespace red
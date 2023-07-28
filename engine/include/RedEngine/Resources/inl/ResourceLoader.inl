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

    if (ptr != nullptr)
        return ptr;

    auto newptr = std::make_shared<Type>(path);

    m_loadedResources.insert({path, newptr});

    return newptr;
}

template <typename Type>
void ResourceLoader<Type>::FinalizeUnusedResources()
{
    for (auto resourceIt = m_loadedResources.begin(); resourceIt != m_loadedResources.end();)
    {
        auto& resource = resourceIt->second;

        if (resource.use_count() == 1)
        {
            FinalizeResource(resource);

            resourceIt = m_loadedResources.erase(resourceIt);
        }

        resourceIt++;
    }
}

template <typename Type>
void ResourceLoader<Type>::FinalizeAllResources()
{
    for (auto resourceIt = m_loadedResources.begin(); resourceIt != m_loadedResources.end(); resourceIt++)
    {
        auto& resource = resourceIt->second;

        FinalizeResource(resource);
    }
}

template <typename Type>
std::shared_ptr<red::IResource> ResourceLoader<Type>::LoadAbstractResource(const Path& path)
{
    return LoadResource(path);
}

template <typename Type>
std::shared_ptr<Type> ResourceLoader<Type>::LoadResource(const Path& path)
{
    using json = Json;

    Path activePath = path;
    activePath.Append(L".json");

    auto cachedResource = GetOrCreateFromCache(activePath);

    if (cachedResource->GetLoadState() != LoadState::STATE_NOT_LOADED)
        return cachedResource;

    cachedResource->SetLoadState(LoadState::STATE_ERROR);

    if (!activePath.Exist() || activePath.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load resource of type {} from path {}", TypeInfo<Type>().name,
                        activePath.GetAscciiPath());
        return cachedResource;
    }

    auto parsedJson = json::parse(ReadFile(activePath), nullptr, false, true);

    if (InitResource(cachedResource, activePath, parsedJson))
    {
        cachedResource->SetLoadState(LoadState::STATE_LOADED);
    }

    RED_LOG_TRACE("Creating {} from path {}", TypeInfo<Type>().name, activePath.GetAscciiPath());

    return cachedResource;
}

}  // namespace red
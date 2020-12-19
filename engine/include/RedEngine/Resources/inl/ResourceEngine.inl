namespace red
{
template <typename IResourceType>
ResourceLoader<IResourceType>* ResourceEngine::GetResourceLoader(ResourceType resourceType)
{
    auto it = m_resourceLoaders.find(resourceType);

    if (it != m_resourceLoaders.end())
    {
        return it->second;
    }

    ResourceLoader<IResourceType>* resourceLoader = new ResourceLoader<IResourceType>();

    m_resourceLoaders.push_back(resourceLoader);

    return resourceLoader;
}
}  // namespace red
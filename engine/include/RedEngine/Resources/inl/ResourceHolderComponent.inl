namespace red
{
template <typename LoaderType>
LoaderType* ResourceHolderComponent::GetResourceLoader()
{
    ResourceType resourceType = LoaderType::ThisType::GetResourceType();

    auto it = m_resourceLoaders.find(resourceType);

    if (it == m_resourceLoaders.end())
    {
        RED_ERROR("ResourceLoader not registered");

        return nullptr;
    }

    return static_cast<LoaderType*>(it->second);
}
}  // namespace red
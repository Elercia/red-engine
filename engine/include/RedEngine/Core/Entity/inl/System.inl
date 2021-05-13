
namespace red
{
template <class... ComponentTypes>
std::vector<Entity*> System::GetComponents()
{
    std::vector<Entity*> selectedEntities;

    for (auto& entityPtr : GetWorldEntities())
    {
        auto list = {entityPtr->HasComponent<ComponentTypes>()...};

        auto v = std::find(list.begin(), list.end(), false);

        if (v == list.end())
        {
            selectedEntities.push_back(entityPtr);
        }
    }

    return selectedEntities;
}

template <typename CT>
CT* System::GetComponent()
{
    return GetSingletonEntity()->GetComponent<CT>();
}

}  // namespace red
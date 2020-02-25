
#include <algorithm>

namespace red
{
template <class... ComponentTypes>
std::vector<std::shared_ptr<Entity>> System::GetComponents()
{
    std::vector<std::shared_ptr<Entity>> selectedEntities;

    for (auto& entityPtr : m_world->GetEntities())
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

}  // namespace red
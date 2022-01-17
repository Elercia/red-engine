
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
template <class... ComponentTypes>
Array<Entity*> System::GetComponents() const
{
    Array<Entity*> selectedEntities;

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

}  // namespace red
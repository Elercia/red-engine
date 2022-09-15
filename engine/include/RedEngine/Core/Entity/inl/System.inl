
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
template <class... ComponentTypes>
Array<std::tuple<Entity*, ComponentTypes*...>, red::DoubleLinearArrayAllocator> System::GetComponents() const
{
    Array<std::tuple<Entity*, ComponentTypes*...>, DoubleLinearArrayAllocator> selectedEntities;

    auto& worldentities = GetWorldEntities();
    for (auto& entityPtr : worldentities)
    {
        auto tuple = std::make_tuple(entityPtr, entityPtr->GetComponent<ComponentTypes>()...);

        constexpr auto size = std::tuple_size_v<decltype( tuple )>;
        bool present [] = {std::get<0>( tuple )!=nullptr, std::get<ComponentTypes*>( tuple ) != nullptr ... };
        bool add = true;

        for( int i = 1; i != size; i++ )
        {
            if( !present[i] )
            {
                add = false;
                break;
            }
        }

        if( add )
            selectedEntities.push_back( tuple );
    }

    return selectedEntities;
}

}  // namespace red
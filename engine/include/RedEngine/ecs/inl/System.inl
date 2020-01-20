#include "../Component.hpp"

namespace red
{

template <typename T>
void System::RequireComponentType()
{
    static_assert(std::is_base_of<Component, T>::value, "System require a valid component");

    auto [insertedComponent, inserted] = m_requiredComponents.insert(T::ComponentName);
}

} // namespace red
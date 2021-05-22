#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"

namespace red
{

red::ComponentData* ComponentRegistry::CreateNewComponentData()
{
    m_componentDatas.resize(m_componentDatas.size() + 1);
    return &(m_componentDatas.back());
}

}
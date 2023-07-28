#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Math/SerializationFunction.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

namespace red
{
template <typename ComponentTypeT, typename MemberTypeT>
void ComponentTraits::AddMember(const String& name, MemberTypeT ComponentTypeT::*memberAddr,
                              const String& tooltip, uint32 flags)
{
    ComponentMemberTraits member;
    member.name = name;
    member.tooltip = tooltip;
    member.flags = flags;

    member.serializationFunction = [=](const Component* comp) -> String {
        // return value serialized as a string
        return Serialize(static_cast<const ComponentTypeT*>(comp)->*memberAddr /*value*/);
    };

    member.deserializationFunction = [=](Component* comp, const String& str) -> bool {
        // deserialize str into value and return true on success, false otherwise
        return Deserialize(static_cast<ComponentTypeT*>(comp)->*memberAddr /*value*/, str);
    };

    if (members.find(name) != members.end())
    {
        RED_LOG_ERROR("Member with name \"{}\" already found in component registry for component \"{}\"", name,
                      TypeInfo<ComponentTypeT>().name);
        RedAbort("Error initializing engine components types"); // we are at startup 
    }

    members[name] = member;
}
}  // namespace red
#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <string_view>

namespace red
{
using EntityId = uint32;

class ILevelComponentData
{
public:
    virtual void AddPairOfValue(const std::string& name, const std::string& value) = 0;
};

class ILevelEntityData
{
public:
    virtual ILevelComponentData* AddLevelComponentData(const std::string& componentName) = 0;
    virtual ILevelEntityData* AddLevelChildEntityData() = 0;

    virtual void SetName(const std::string& name) = 0;
    virtual void SetId(const EntityId& name) = 0;
    virtual void SetParentId(const EntityId& name) = 0;
};

class ILevelData
{
public:
    virtual ILevelEntityData* AddLevelEntityData() = 0;
};
}  // namespace red
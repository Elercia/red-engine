#pragma once

#include "../Utils/Uncopyable.hpp"

#include "RedEngine/Core/EngineConfig.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <type_traits>

namespace red
{
class SubEngine : public Uncopyable
{
public:
    virtual ~SubEngine() = default;

    virtual void Init(const EngineInitDesc& /*initDesc*/){};
};

template <class T>
void ApplyInit(T& subEngine, const EngineInitDesc& initDesc)
{
    static_assert(std::is_base_of<SubEngine, T>::value,
                  "A subengine added to the Engine class is not a SubEngine type");

    subEngine.Init(initDesc);
};

}  // namespace red

#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <type_traits>

#include <RedEngine/Core/EngineConfig.hpp>
#include "../Utils/Uncopyable.hpp"

namespace red
{
class SubEngine : public Uncopyable
{
public:
    virtual void Init(const EngineInitDesc& initDesc){};
};

template <class T>
void ApplyInit(T& subEngine, const EngineInitDesc& initDesc)
{
    static_assert(std::is_base_of<SubEngine, T>::value,
                  "A subengine added to the Engine class is not a SubEngine type");

    subEngine.Init(initDesc);
};

}  // namespace red

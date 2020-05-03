#pragma once

#include <type_traits>

#include "../Utils/Uncopyable.hpp"

class SubEngine : public Uncopyable
{
public:
    virtual void Init(){};
};

template <class T>
void ApplyInit(T& subEngine)
{
    static_assert(std::is_base_of<SubEngine, T>::value,
                  "A subengine added to the Engine class is not a SubEngine type");

    subEngine.Init();
};
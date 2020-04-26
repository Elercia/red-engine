#pragma once

#include <RedEngine/Core/SubEngine.hpp>

namespace red
{
class LevelManager : public SubEngine
{
public:
    LevelManager();
    ~LevelManager();

    template <class T>
    static void RegisterLevel();
};
}  // namespace red

#include "inl/LevelManager.inl"
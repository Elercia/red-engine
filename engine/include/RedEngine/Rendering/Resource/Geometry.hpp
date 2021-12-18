#pragma once

#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
class Geometry : public IResource
{
public:
    Geometry();
    ~Geometry();

private:
    Array<float> m_vertices;
};
}

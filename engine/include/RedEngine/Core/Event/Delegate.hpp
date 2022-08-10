#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <cstdint>
#include <functional>

namespace red
{

template <typename... Args>
class Delegate : public Uncopyable
{
public:
    using FuncIndex = uint16_t;
    using FuncType = std::function<void(Args...)>;

    Delegate();
    ~Delegate();

    FuncIndex Add(FuncType func);
    void Remove(FuncIndex index);

    /// Invoke all
    void operator()(Args... args);

private:
    Map<FuncIndex, FuncType> m_functions;
    FuncIndex m_nextIndex;
};

}  // namespace red

#include "inl/Delegate.inl"

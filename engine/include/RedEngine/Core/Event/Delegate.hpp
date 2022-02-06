#pragma once

#include "RedEngine/Utils/Uncopyable.hpp"

#include <cstdint>
#include <functional>
#include <map>

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
    std::map<FuncIndex, FuncType> m_functions;
    FuncIndex m_nextIndex;
};

}  // namespace red

#include "inl/Delegate.inl"
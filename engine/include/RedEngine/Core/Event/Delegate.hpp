#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <cstdint>
#include <functional>
#include <map>

namespace red
{
using FuncIndex = uint16_t;

template <typename... Args>
class Delegate : public Uncopyable
{
public:
    Delegate();
    ~Delegate();

    FuncIndex Add(std::function<void(Args...)> func);
    void Remove(FuncIndex index);

    /// Invoke all
    void operator()(Args... args);

private:
    std::map<FuncIndex, std::function<void(Args...)>> m_functions;
    FuncIndex m_nextIndex;
};

}  // namespace red

#include "inl/Delegate.inl"
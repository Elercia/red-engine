#pragma once

#include <RedEngine/RedEngineBase.hpp>

class Uncopyable
{
public:
    Uncopyable() = default;
    ~Uncopyable() = default;

    Uncopyable(const Uncopyable& other) = delete;
    Uncopyable(Uncopyable&& other) = default;

    const Uncopyable& operator=(const Uncopyable& other) = delete;
    Uncopyable& operator=(Uncopyable&& other) = default;
};
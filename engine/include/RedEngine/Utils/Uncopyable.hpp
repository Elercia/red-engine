#pragma once

namespace red
{
class Uncopyable
{
public:
    Uncopyable() = default;
    ~Uncopyable() = default;

    Uncopyable(const Uncopyable& other) = delete;
    Uncopyable& operator=(const Uncopyable& other) = delete;

    Uncopyable(Uncopyable&& other) = default;
    Uncopyable& operator=(Uncopyable&& other) = default;
};

class Unmovable
{
public:
    Unmovable() = default;
    ~Unmovable() = default;

    Unmovable(Uncopyable&& other) = delete;
    Unmovable& operator=(Uncopyable&& other) = delete;

    Unmovable(const Unmovable& other) = default;
    Unmovable& operator=(const Unmovable& other) = default;
};
}  // namespace red

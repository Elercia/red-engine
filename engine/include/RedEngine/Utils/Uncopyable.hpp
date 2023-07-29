#pragma once

namespace red
{
class Uncopyable
{
public:
    Uncopyable() = default;
    ~Uncopyable() = default;

    Uncopyable(const Uncopyable& other) = delete;
    const Uncopyable& operator=(const Uncopyable& other) = delete;
};

class Unmovable
{
public:
    Unmovable() = default;
    ~Unmovable() = default;

    Unmovable(Uncopyable&& other) = delete;
    Unmovable& operator=(Uncopyable&& other) = delete;
};
}  // namespace red

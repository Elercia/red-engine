#pragma once

class MyClass
{
public:
    MyClass() = default;
    ~MyClass() = default;

    int m_a{-1};

    void op(int a) { m_a = a; }

};
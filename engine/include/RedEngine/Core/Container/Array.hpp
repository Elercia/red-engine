#pragma once

#include <initializer_list>
#include <cstdlib>

#include <RedEngine/RedEngineBase.hpp>

namespace red
{
template <typename T>
class Array
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    using reference = T&;
    using const_reference = const T&;

    using size_type = int;

    static constexpr size_t size_of_type = sizeof(T);

    /// Constructors
    Array();
    ~Array();

    Array(std::initializer_list<T> list);

    Array(const Array& other) = delete;
    void operator=(const Array& other) = delete;

    Array(Array&& other) = default;
    Array& operator=(Array&& other) = default;

    /// Accessors
    const_reference operator[](size_type index) const;
    reference operator[](size_type index);

    const_reference at(size_type index) const;
    reference at(size_type index);

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    T* data();
    const T* data() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    /// Capacity and size
    bool empty() const;

    size_type size() const;
    size_type capacity() const;

    void reserve(size_type capacity);
    void shrink_to_fit();

    void clear();

    void resize(size_type count, T value = T());

    /// Modifiers
    iterator insert(iterator pos, const T& value);
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    void insert(iterator pos, size_type count, const T& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    iterator insert(const_iterator pos, std::initializer_list<T> list);

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const T& value);
    void push_back(T&& value);

    template <class... Args>
    void emplace_back(Args&&... args);
    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    void pop_back();

    void assign(size_type count, const T& value);
    template <class InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);

private:
    void SetCapacity(size_type newCapacity);
    void SmartReserve(size_type capacity);
    void Resize(size_type count, const T& t);
    void Destroy(size_type from, size_type to);

    size_type m_size;
    size_type m_capacity;
    T* m_data;
};
}  // namespace red

#include "inl/Array.inl"
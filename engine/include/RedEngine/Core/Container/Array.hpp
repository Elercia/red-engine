#pragma once

#define RED_USE_ARRAY
#ifdef RED_USE_ARRAY

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Macros.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <cstdlib>
#include <initializer_list>

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

    using size_type = uint64;

    /// Constructors
    Array();
    ~Array();

    Array(std::initializer_list<T> list);

    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);

    Array(Array<T>&& other);
    Array<T>& operator=(Array<T>&& other);

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

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const T& value);
    void push_back(T&& value);

    template <class... Args>
    reference emplace_back(Args&&... args);

    void pop_back();

    template <class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last);

private:
    void SetCapacity(size_type askedCapacity);
    void Resize(size_type count, const T& t);
    void Destroy(size_type from, size_type to);
    void Destroy(iterator from, iterator to);

    size_type m_size{0};
    size_type m_capacity{0};
    T* m_data{nullptr};
};
}  // namespace red
#else  // RED_USE_ARRAY

#include <vector>

namespace red
{
template <typename T>
using Array = std::vector<T>;
}  // namespace red

#endif  // else RED_USE_ARRAY

#include "inl/Array.inl"
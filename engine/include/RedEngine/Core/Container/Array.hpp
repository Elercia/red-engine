#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <cstdlib>
#include <initializer_list>
#include <vector>

namespace red
{
#ifdef RED_USE_ARRAY

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
    FORCEINLINE const_reference operator[](size_type index) const;
    FORCEINLINE reference operator[](size_type index);

    FORCEINLINE const_reference at(size_type index) const;
    FORCEINLINE reference at(size_type index);

    FORCEINLINE reference front();
    FORCEINLINE const_reference front() const;

    FORCEINLINE reference back();
    FORCEINLINE const_reference back() const;

    FORCEINLINE T* data();
    FORCEINLINE const T* data() const;

    FORCEINLINE iterator begin();
    FORCEINLINE const_iterator begin() const;
    FORCEINLINE const_iterator cbegin() const;

    FORCEINLINE iterator end();
    FORCEINLINE const_iterator end() const;
    FORCEINLINE const_iterator cend() const;

    /// Capacity and size
    FORCEINLINE bool empty() const;

    FORCEINLINE size_type size() const;
    FORCEINLINE size_type capacity() const;

    void reserve(size_type capacity);
    void shrink_to_fit();

    void clear();

    void resize(size_type count, T value = T());

    /// Modifiers
    /*iterator insert(iterator pos, const T& value);
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    void insert(iterator pos, size_type count, const T& value);
    iterator insert(const_iterator pos, size_type count, const T& value);
    iterator insert(const_iterator pos, std::initializer_list<T> list);*/

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const T& value);
    void push_back(T&& value);

    template <class... Args>
    reference emplace_back(Args&&... args);

    void pop_back();

private:
    FORCEINLINE void SetCapacity(size_type newCapacity);
    FORCEINLINE void SmartReserve(size_type capacity);
    FORCEINLINE void Resize(size_type count, const T& t);
    FORCEINLINE void Destroy(size_type from, size_type to);
    FORCEINLINE void Destroy(iterator from, iterator to);

    size_type m_size;
    size_type m_capacity;
    T* m_data;
};
#else  // RED_USE_ARRAY

template <typename T>
using Array = std::vector<T>;

#endif  // else RED_USE_ARRAY
}  // namespace red

#include "inl/Array.inl"
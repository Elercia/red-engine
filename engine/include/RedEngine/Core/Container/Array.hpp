#pragma once

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
    RED_FORCEINLINE const_reference operator[](size_type index) const;
    RED_FORCEINLINE reference operator[](size_type index);

    RED_FORCEINLINE const_reference at(size_type index) const;
    RED_FORCEINLINE reference at(size_type index);

    RED_FORCEINLINE reference front();
    RED_FORCEINLINE const_reference front() const;

    RED_FORCEINLINE reference back();
    RED_FORCEINLINE const_reference back() const;

    RED_FORCEINLINE T* data();
    RED_FORCEINLINE const T* data() const;

    RED_FORCEINLINE iterator begin();
    RED_FORCEINLINE const_iterator begin() const;
    RED_FORCEINLINE const_iterator cbegin() const;

    RED_FORCEINLINE iterator end();
    RED_FORCEINLINE const_iterator end() const;
    RED_FORCEINLINE const_iterator cend() const;

    /// Capacity and size
    RED_FORCEINLINE bool empty() const;

    RED_FORCEINLINE size_type size() const;
    RED_FORCEINLINE size_type capacity() const;

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
    RED_FORCEINLINE void SetCapacity(size_type newCapacity);
    RED_FORCEINLINE void SmartReserve(size_type capacity);
    RED_FORCEINLINE void Resize(size_type count, const T& t);
    RED_FORCEINLINE void Destroy(size_type from, size_type to);
    RED_FORCEINLINE void Destroy(iterator from, iterator to);

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
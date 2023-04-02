#pragma once

#define RED_USE_ARRAY
#ifdef RED_USE_ARRAY

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Macros.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Core/Memory/MemoryProfiler.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <cstdlib>
#include <initializer_list>

namespace red
{
struct DefaultAllocator
{
    inline void* Allocate(uint32 size);
    inline void Free(void* ptr);
    inline void* Realloc(void* ptr, uint32 oldSize, uint32 size);
};

template <typename T, typename Allocator = DefaultAllocator>
class Array
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    using reference = T&;
    using const_reference = const T&;

    using size_type = uint32;
    static const size_type npos = (size_type)-1;

    /// Constructors
    Array();
    ~Array();

    Array(std::initializer_list<T> list);

    template <typename OtherAllocator>
    Array(const Array<T, OtherAllocator>& other);

    template <typename OtherAllocator>
    Array& operator=(const Array<T, OtherAllocator>& other);

    Array(const Array& other);
    Array& operator=(const Array& other);

    Array(Array&& other);
    Array& operator=(Array&& other);

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
    void clearAndFree();

    void resize(size_type count);
    void resize(size_type count, const T& t);

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

    size_type Find(const T& toFind) const;

    template <typename Predicate>
    size_type FindIf(Predicate&& pred) const;

private:
    void SetCapacity(size_type askedCapacity);
    void Destroy(size_type from, size_type to);
    void Destroy(iterator from, iterator to);

    Allocator m_allocator;
    size_type m_size;
    size_type m_capacity;
    T* m_data;
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

namespace red
{
template <typename T>
class ArrayView
{
    using size_type = uint32;
    using iterator = T*;
    using const_iterator = const T*;

public:
    ArrayView();

    template <typename A>
    explicit ArrayView(Array<T, A>& ar);

    template <typename A>
    ArrayView(Array<T, A>& ar, size_type start, size_type count);

    template <typename A>
    ArrayView(Array<T, A>& ar, size_type count);

    ArrayView(T* data, size_type count);
    ArrayView(T* data, size_type start, size_type count);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    bool empty() const;
    size_type size() const;
    T* data();

    T& operator[](size_type index);
    const T& operator[](size_type index) const;

private:
    T* m_offsetData;
    size_type m_count;
};
}  // namespace red

#include "inl/Array.inl"

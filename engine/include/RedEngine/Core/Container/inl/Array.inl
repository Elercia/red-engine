#include "RedEngine/Math/Math.hpp"

namespace red
{
#ifdef RED_USE_ARRAY

template <typename T>
Array<T>::Array() : m_size(0), m_capacity(0), m_data(nullptr)
{
}

template <typename T>
Array<T>::Array(std::initializer_list<T> list) : m_size(0), m_capacity(0), m_data(nullptr)
{
    reserve(list.size());

    for (auto it = list.begin(); it != list.end(); it++)
        push_back(*it);
}

template <typename T>
Array<T>::~Array()
{
    Destroy(begin(), end());
    RED_SAFE_FREE(m_data);
}

template <typename T>
Array<T>::Array(const Array<T>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }

    return *this;
}

template <typename T>
Array<T>::Array(Array<T>&& other)
    : m_size(std::move(other.m_size)), m_capacity(std::move(other.m_capacity)), m_data(std::move(other.m_data))
{
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
    m_size = std::move(other.m_size);
    m_capacity = std::move(other.m_capacity);
    m_data = std::move(other.m_data);

    return *this;
}

template <typename T>
template <typename... Args>
typename Array<T>::reference Array<T>::emplace_back(Args&&... args)
{
    size_type index = m_size;
    size_type newSize = m_size + 1;

    reserve(newSize);

    m_size = newSize;

    new (m_data + index) T(std::forward<Args>(args)...);

    return m_data[index];
}

template <typename T>
void Array<T>::resize(size_type count, T value /*= T()*/)
{
    Resize(count, value);
}

template <typename T>
void Array<T>::Resize(size_type count, const T& t)
{
    for (size_type i = m_size; i < count; i++)
    {
        push_back(t);
    }
}

template <typename T>
void Array<T>::pop_back()
{
    Destroy(m_size - 1, m_size);

    m_size--;
}

template <typename T>
void Array<T>::push_back(T&& value)
{
    reserve(m_size + 1);
    m_data[m_size] = value;
    m_size++;
}

template <typename T>
void Array<T>::push_back(const T& value)
{
    reserve(m_size + 1);

    m_data[m_size] = value;
    m_size++;
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(const_iterator first, const_iterator last)
{
    RED_ASSERT_S(last >= first);
    RED_ASSERT_S(first >= begin());
    RED_ASSERT_S(last <= end());

    iterator index = const_cast<iterator>(first);
    iterator shift = const_cast<iterator>(last);

    const_iterator endIt = end();

    Destroy(index, shift);

    while (shift < endIt)
    {
        *index = *shift;
        index++;
        shift++;
    }

    size_type valueErased = (size_type) (last - first);

    m_size -= valueErased;

    reserve(m_size);

    return const_cast<iterator>(first);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator first, iterator last)
{
    return erase((const_iterator) first, (const_iterator) last);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(const_iterator pos)
{
    return erase(pos, pos + 1);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator pos)
{
    return erase((const_iterator) pos);
}

template <typename T>
void Array<T>::clear()
{
    Destroy(begin(), end());
    m_size = 0;
}

template <typename T>
void Array<T>::shrink_to_fit()
{
    SetCapacity(m_size);
}

template <typename T>
void Array<T>::reserve(size_type capacity)
{
    if (capacity < m_size || capacity <= m_capacity)
    {
        return;
    }

    capacity = Math::NextPowerOf2(capacity);

    SetCapacity(capacity);
}

template <typename T>
void Array<T>::SetCapacity(size_type askedCapacity)
{
    if (askedCapacity < m_size)
        return;

    T* tmp = nullptr;

    if (askedCapacity != 0)
    {
        auto capacitySize = askedCapacity * sizeof(T);
        tmp = (T*)realloc(m_data, capacitySize);

        if (tmp == NULL)
        {
            RED_LOG_ERROR("Not enough space to realloc {} bytes of memory", capacitySize);
            RED_ABORT("OutOfMemory");
        }
    }

    m_data = tmp;
    m_capacity = askedCapacity;
}

template <typename T>
typename Array<T>::size_type Array<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
typename Array<T>::size_type Array<T>::size() const
{
    return m_size;
}

template <typename T>
bool Array<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::cend() const
{
    return end();
}

template <typename T>
typename Array<T>::const_iterator Array<T>::end() const
{
    return m_data + m_size;
}

template <typename T>
typename Array<T>::iterator Array<T>::end()
{
    return m_data + m_size;
}

template <typename T>
typename Array<T>::const_iterator Array<T>::cbegin() const
{
    return begin();
}

template <typename T>
typename Array<T>::const_iterator Array<T>::begin() const
{
    return m_data;
}

template <typename T>
typename Array<T>::iterator Array<T>::begin()
{
    return m_data;
}

template <typename T>
const T* Array<T>::data() const
{
    return m_data;
}

template <typename T>
T* Array<T>::data()
{
    return m_data;
}

template <typename T>
typename Array<T>::const_reference Array<T>::back() const
{
    return m_data[m_size - 1];
}

template <typename T>
typename Array<T>::reference Array<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
typename Array<T>::const_reference Array<T>::front() const
{
    return m_data[0];
}

template <typename T>
typename Array<T>::reference Array<T>::front()
{
    return m_data[0];
}

template <typename T>
typename Array<T>::reference Array<T>::at(size_type index)
{
    RED_ASSERT_S(index < m_size);
    return m_data[index];
}

template <typename T>
typename Array<T>::const_reference Array<T>::at(size_type index) const
{
    RED_ASSERT_S(index < m_size);
    return m_data[index];
}

template <typename T>
typename Array<T>::reference Array<T>::operator[](size_type index)
{
    return at(index);
}

template <typename T>
typename Array<T>::const_reference Array<T>::operator[](size_type index) const
{
    return at(index);
}

template <typename T>
template <class InputIterator>
typename Array<T>::iterator Array<T>::insert(const_iterator position, InputIterator first, InputIterator last)
{
    size_type nbElem = (size_type) (last - first);
    reserve(m_size + nbElem);

    // move elements from [position;end] to [position+nbElem; end+nbElem]
    for (auto it = (iterator) position; it != end(); ++it)
    {
        *(it + nbElem) = *it;
    }

    // copy elements from [first;last] to [position; position+nbElem]
    iterator itTo = (iterator) position;
    for (auto itFrom = first; itFrom != last; ++itFrom, ++itTo)
    {
        *itTo = *itFrom;
    }

    return (iterator) position;
}

template <typename T>
void Array<T>::Destroy(size_type from, size_type to)
{
    iterator fromIt = m_data + from;
    iterator toIt = m_data + to;

    Destroy(fromIt, toIt);
}

template <typename T>
void Array<T>::Destroy(iterator from, iterator to)
{
    if constexpr (!std::is_trivially_destructible<T>::value)
    {
        for (iterator it = from; it < to; it++)
        {
            it->~T();
        }
    }
}
#endif  // RED_USE_ARRAY
}  // namespace red
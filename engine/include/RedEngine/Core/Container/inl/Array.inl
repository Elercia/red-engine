
namespace red
{
#ifdef RED_USE_ARRAY

void* DefaultAllocator ::Allocate(uint32 size)
{
    return red_malloc(size);
}

void DefaultAllocator::Free(void* ptr)
{
    red_free(ptr);
}

void* DefaultAllocator::Realloc(void* ptr, uint32 /*oldSize*/, uint32 size)
{
    return red_realloc(ptr, size);
}

template <typename T, typename Allocator>
Array<T, Allocator>::Array()
{
}

template <typename T, typename Allocator>
Array<T, Allocator>::Array(std::initializer_list<T> list)
{
    reserve((uint32) list.size());

    for (auto it = list.begin(); it != list.end(); it++)
        push_back(*it);
}

template <typename T, typename Allocator>
Array<T, Allocator>::~Array()
{
    Destroy(begin(), end());
    Allocator::Free(m_data);
}

template <typename T, typename Allocator>
template <typename OtherAllocator>
Array<T, Allocator>::Array(const Array<T, OtherAllocator>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }
}

template <typename T, typename Allocator>
Array<T, Allocator>::Array(const Array<T, Allocator>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }
}

template <typename T, typename Allocator>
template <typename OtherAllocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(const Array<T, OtherAllocator>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }

    return *this;
}

template <typename T, typename Allocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(const Array<T, Allocator>& other)
{
    reserve(other.m_size);

    for (auto& it : other)
    {
        push_back(it);
    }

    return *this;
}

template <typename T, typename Allocator>
Array<T, Allocator>::Array(Array<T, Allocator>&& other)
    : m_size(std::move(other.m_size)), m_capacity(std::move(other.m_capacity)), m_data(std::move(other.m_data))
{
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

template <typename T, typename Allocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(Array<T, Allocator>&& other)
{
    Destroy(begin(), end());
    Allocator::Free(m_data);

    m_size = std::move(other.m_size);
    m_capacity = std::move(other.m_capacity);
    m_data = std::move(other.m_data);

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;

    return *this;
}

template <typename T, typename Allocator>
template <typename... Args>
typename Array<T, Allocator>::reference Array<T, Allocator>::emplace_back(Args&&... args)
{
    size_type index = m_size;
    size_type newSize = m_size + 1;

    reserve(newSize);

    m_size = newSize;

    new (m_data + index) T(std::forward<Args>(args)...);

    return m_data[index];
}

template <typename T, typename Allocator>
void Array<T, Allocator>::resize(size_type count)
{
    reserve(count);

    for (size_type i = m_size; i < count; i++)
    {
        new (m_data + i) T();
    }

    m_size = count;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::resize(size_type count, const T& t)
{
    reserve(count);
    for (size_type i = m_size; i < count; i++)
    {
        push_back(t);
    }
}

template <typename T, typename Allocator>
void Array<T, Allocator>::pop_back()
{
    Destroy(m_size - 1, m_size);

    m_size--;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::push_back(T&& value)
{
    reserve(m_size + 1);
    new (m_data + m_size) T(std::move(value));
    m_size++;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::push_back(const T& value)
{
    reserve(m_size + 1);
    new (m_data + m_size) T(value);
    m_size++;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::erase(const_iterator first, const_iterator last)
{
    RedAssert(last >= first);
    RedAssert(first >= begin());
    RedAssert(last <= end());

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

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::erase(iterator first, iterator last)
{
    return erase((const_iterator) first, (const_iterator) last);
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::erase(const_iterator pos)
{
    return erase(pos, pos + 1);
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::erase(iterator pos)
{
    return erase((const_iterator) pos);
}

template <typename T, typename Allocator>
void Array<T, Allocator>::clear()
{
    Destroy(begin(), end());
    m_size = 0;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::clearAndFree()
{
    Destroy(begin(), end());
    Allocator::Free(m_data);
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::shrink_to_fit()
{
    SetCapacity(m_size);
}

template <typename T, typename Allocator>
void Array<T, Allocator>::reserve(size_type capacity)
{
    if (capacity < m_size || capacity <= m_capacity)
    {
        return;
    }

    capacity = Math::NextPowerOf2(capacity);

    SetCapacity(capacity);
}

template <typename T, typename Allocator>
void Array<T, Allocator>::SetCapacity(size_type askedCapacity)
{
    if (askedCapacity < m_size)
        return;

    if (askedCapacity != 0)
    {
        uint32 capacitySize = askedCapacity * sizeof(T);
        if constexpr (std::is_trivially_constructible_v<T> && std::is_trivially_destructible_v<T>)
        {
            T* tmp = (T*) Allocator::Realloc(m_data, m_capacity * sizeof(T), capacitySize);

            if (tmp == NULL)
            {
                RedAbort("OutOfMemory");
            }

            m_data = tmp;
        }
        else
        {
            T* tmp = (T*) Allocator::Allocate(capacitySize);

            if (tmp == NULL)
            {
                RedAbort("OutOfMemory");
            }

            // Copy members from old location to the new one
            for (size_type i = 0; i < m_size; i++)
            {
                new (tmp + i) T(std::move(m_data[i]));
                m_data[i].~T();
            }

            Allocator::Free(m_data);
            m_data = tmp;
        }
    }

    m_capacity = askedCapacity;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::size_type Array<T, Allocator>::capacity() const
{
    return m_capacity;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::size_type Array<T, Allocator>::size() const
{
    return m_size;
}

template <typename T, typename Allocator>
bool Array<T, Allocator>::empty() const
{
    return m_size == 0;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_iterator Array<T, Allocator>::cend() const
{
    return end();
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_iterator Array<T, Allocator>::end() const
{
    return m_data + m_size;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::end()
{
    return m_data + m_size;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_iterator Array<T, Allocator>::cbegin() const
{
    return begin();
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_iterator Array<T, Allocator>::begin() const
{
    return m_data;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::begin()
{
    return m_data;
}

template <typename T, typename Allocator>
const T* Array<T, Allocator>::data() const
{
    return m_data;
}

template <typename T, typename Allocator>
T* Array<T, Allocator>::data()
{
    return m_data;
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_reference Array<T, Allocator>::back() const
{
    return m_data[m_size - 1];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::reference Array<T, Allocator>::back()
{
    return m_data[m_size - 1];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_reference Array<T, Allocator>::front() const
{
    return m_data[0];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::reference Array<T, Allocator>::front()
{
    return m_data[0];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::reference Array<T, Allocator>::at(size_type index)
{
    RedAssert(index < m_size);
    return m_data[index];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_reference Array<T, Allocator>::at(size_type index) const
{
    RedAssert(index < m_size);
    return m_data[index];
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::reference Array<T, Allocator>::operator[](size_type index)
{
    return at(index);
}

template <typename T, typename Allocator>
typename Array<T, Allocator>::const_reference Array<T, Allocator>::operator[](size_type index) const
{
    return at(index);
}

template <typename T, typename Allocator>
template <class InputIterator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::insert(const_iterator position, InputIterator first,
                                                                   InputIterator last)
{
    const size_type nbElem = (size_type) (last - first);
    const size_type positionIndex = (size_type) (position - m_data);
    if (nbElem == 0)
        return (iterator) position;

    RedAssert(position >= begin() && position <= end(), "Position is out of range");
    RedAssert(first < last, "Invalid insertion");

    reserve(m_size + nbElem);  // position interator is now invalid due to possible allocation change

    if (m_size > 0)
    {
        // move elements from [position;end] to [position+nbElem; end+nbElem]
        for (auto i = positionIndex; i < m_size; ++i)
        {
            new (m_data + i + nbElem) T(std::move(*(m_data + i)));
            (m_data + i)->~T();
        }
    }

    // copy elements from [first;last] to [position; position+nbElem]
    iterator itFrom = (iterator) first;
    for (size_type i = 0; i < nbElem; i++)
    {
        new (m_data + i + positionIndex) T(*itFrom);

        itFrom++;
    }

    m_size += nbElem;

    return (iterator) position;
}

template <typename T, typename Allocator>
void Array<T, Allocator>::Destroy(size_type from, size_type to)
{
    iterator fromIt = m_data + from;
    iterator toIt = m_data + to;

    Destroy(fromIt, toIt);
}

template <typename T, typename Allocator>
void Array<T, Allocator>::Destroy(iterator from, iterator to)
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

template <typename T>
ArrayView<T>::ArrayView() : m_offsetData(nullptr), m_count(0)
{
}

template <typename T>
template <typename A>
ArrayView<T>::ArrayView(Array<T, A>& ar) : m_offsetData(ar.data()), m_count(ar.size())
{
}

template <typename T>
template <typename A>
ArrayView<T>::ArrayView(Array<T, A>& ar, size_type start, size_type count)
    : m_offsetData(ar.data() + start), m_count(count)
{
}

template <typename T>
template <typename A>
ArrayView<T>::ArrayView(Array<T, A>& ar, size_type count) : m_offsetData(ar.data()), m_count(count)
{
}

template <typename T>
ArrayView<T>::ArrayView(T* data, size_type count) : m_offsetData(data), m_count(count)
{
}

template <typename T>
ArrayView<T>::ArrayView(T* data, size_type start, size_type count) : m_offsetData(data + start), m_count(count)
{
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::begin()
{
    return m_offsetData;
}

template <typename T>
typename ArrayView<T>::const_iterator ArrayView<T>::begin() const
{
    return m_offsetData;
}

template <typename T>
typename ArrayView<T>::iterator ArrayView<T>::end()
{
    return m_offsetData + m_count;
}

template <typename T>
typename ArrayView<T>::const_iterator ArrayView<T>::end() const
{
    return m_offsetData + m_count;
}

template <typename T>
ArrayView<T>::size_type ArrayView<T>::size() const
{
    return m_count;
}

template <typename T>
bool ArrayView<T>::empty() const
{
    return m_count == 0;
}

template <typename T>
T* ArrayView<T>::data()
{
    return m_offsetData;
}

template <typename T>
T& ArrayView<T>::operator[](size_type index)
{
    return m_offsetData[index];
}

template <typename T>
const T& ArrayView<T>::operator[](size_type index) const
{
    return m_offsetData[index];
}

}  // namespace red

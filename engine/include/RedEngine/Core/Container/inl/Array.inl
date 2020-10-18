namespace red
{
template <typename T>
template <typename... Args>
typename Array<T>::iterator Array<T>::emplace(const_iterator pos, Args&&... args)
{
    reserve(m_size + 1);
    m_data[m_size] = T(std::forward<Args>(args)...);
    m_size++;
    return &m_data[m_size - 1];
}

template <typename T>
template <typename... Args>
void Array<T>::emplace_back(Args&&... args)
{
    reserve(m_size + 1);
    m_data[m_size] = T(std::forward<Args>(args)...);
    m_size++;
}

template <typename T>
void Array<T>::resize(size_type count, const T& value)
{
    Resize(count, value);
}

template <typename T>
void Array<T>::resize(size_type count)
{
    Resize(count, T());
}

template <typename T>
void Array<T>::resize(size_type count, T value /*= T()*/)
{
    Resize(count, value);
}

template <typename T>
void Array<T>::Resize(size_type count, const T& t)
{
    if (m_size < count)
    {
        for (int i = m_size; i < count; i++)
        {
            push_back(t);
        }
    }
}

template <typename T>
void Array<T>::pop_back()
{
    reserve(m_size - 1);
    m_size--;
}

template <typename T>
void Array<T>::push_back(T&& value)
{
    reserve(m_size + 1);
    m_data[m_size] = std::move(value);
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
    RED_ASSERT_S(last > first);
    RED_ASSERT_S(first > begin());
    RED_ASSERT_S(last <= end());

    size_type valueErased = last - first;

    m_size -= valueErased;

    iterator shift = last;
    iterator index = first;

    const_iterator end = end();

    while (shift < end)
    {
        *index = std::move(*shift);
        index++;
        shift++;
    }

    return shift;
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator first, iterator last)
{
    return erase((const_iterator) first, (const_iterator) last);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(const_iterator pos)
{
    return erase(pos, pos);
}

template <typename T>
typename Array<T>::iterator Array<T>::erase(iterator pos)
{
    return erase((const_iterator) pos);
}

template <typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator pos, std::initializer_list<T> ilist)
{
    reserve(m_size + ilist.size());



    m_size++;
}

template <typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator pos, size_type count, const T& value)
{
    reserve(m_size + count);
}

template <typename T>
void Array<T>::insert(iterator pos, size_type count, const T& value)
{
    return insert((const_iterator)pos, count, value);
}

template <typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator pos, T&& value)
{
    reserve(m_size + 1);
}

template <typename T>
typename Array<T>::iterator Array<T>::insert(const_iterator pos, const T& value)
{
    reserve(m_size + 1);
}

template <typename T>
typename Array<T>::iterator Array<T>::insert(iterator pos, const T& value)
{
    reserve(m_size + 1);
}

template <typename T>
void Array<T>::clear()
{
    SetCapacity(0);
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
    if (capacity < m_size)
    {
        RED_ERROR("Couldnt reserve a size below size");
        return;
    }

    size_type newCapacity = m_capacity;

    if (capacity > m_capacity)
    {
        // If the asked capacity is not above our increment
        if (capacity < m_capacity + CapacitySizeIncrement)
            newCapacity = m_capacity + CapacitySizeIncrement;
        else
            newCapacity = capacity;
    }
    else if (capacity < m_capacity)
    {
        if (capacity > m_capacity - CapacitySizeIncrement)
            return;  // the current capacity can hold the ask capacity
        else
            newCapacity = capacity;
    }

    SetCapacity(newCapacity);
}

template <typename T>
void Array<T>::SetCapacity(size_type askedCapacity)
{
    m_data = (T*)realloc(m_data, askedCapacity);
    m_capacity = askedCapacity;
    RED_ASSERT_S(m_data != nullptr);
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
    RED_ASSERT_S(m_size > 0);
    return m_data[m_size - 1];
}

template <typename T>
typename Array<T>::const_iterator Array<T>::end() const
{
    RED_ASSERT_S(m_size > 0);
    return m_data[m_size - 1];
}

template <typename T>
typename Array<T>::iterator Array<T>::end()
{
    RED_ASSERT_S(m_size > 0);
    return m_data[m_size - 1];
}

template <typename T>
typename Array<T>::const_iterator Array<T>::cbegin() const
{
    RED_ASSERT_S(m_size > 0);
    return m_data[0];
}

template <typename T>
typename Array<T>::const_iterator Array<T>::begin() const
{
    RED_ASSERT_S(m_size > 0);
    return m_data[0];
}

template <typename T>
typename Array<T>::iterator Array<T>::begin()
{
    RED_ASSERT_S(m_size > 0);
    return m_data[0];
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
    RED_ASSERT_S(m_size > 0);
    return *(m_data[m_size - 1]);
}

template <typename T>
typename Array<T>::reference Array<T>::back()
{
    RED_ASSERT_S(m_size > 0);
    return *(m_data[m_size - 1]);
}

template <typename T>
typename Array<T>::const_reference Array<T>::front() const
{
    RED_ASSERT_S(m_size > 0);
    return m_data[0];
}

template <typename T>
typename Array<T>::reference Array<T>::front()
{
    RED_ASSERT_S(m_size > 0);
    return m_data[0];
}

template <typename T>
typename Array<T>::reference Array<T>::at(size_type index)
{
    RED_ASSERT_S(m_size > index);
    return m_data[index];
}

template <typename T>
typename Array<T>::const_reference Array<T>::at(size_type index) const
{
    RED_ASSERT_S(m_size > index);
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
Array<T>::Array() : m_size(0), m_capacity(0), m_data(nullptr)
{
    SetCapacity(Array<T>::CapacitySizeIncrement);
}

template <typename T>
Array<T>::Array(std::initializer_list<T> list)
{
    insert(end(), l.begin(), l.end());
}

template <typename T>
Array<T>::~Array()
{
    RED_SAFE_DELETE(m_data);
}
}  // namespace red
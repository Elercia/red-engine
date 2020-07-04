
namespace red
{
template <class T>
ObjectHandle<T>::ObjectHandle(T* value) : m_value(value)
{
}

template <class T>
ObjectHandle<T>::ObjectHandle(const ObjectHandle<T>& other) : m_value(other.m_value)
{
}
template <class T>
ObjectHandle<T>& ObjectHandle<T>::operator=(const ObjectHandle<T>& other)
{
    m_value = other.m_value;
    return *this;
}

template <class T>
T* ObjectHandle<T>::operator->()
{
    return m_value;
}
}  // namespace red
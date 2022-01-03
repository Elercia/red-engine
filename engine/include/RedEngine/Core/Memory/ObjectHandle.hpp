#pragma once

namespace red
{
template <class T>
class ObjectHandle
{
public:
    explicit ObjectHandle(T* value);
    ObjectHandle(const ObjectHandle<T>& other);
    ObjectHandle(ObjectHandle<T>&&) = default;
    ~ObjectHandle() = default;

    ObjectHandle<T>& operator=(const ObjectHandle<T>& other);
    ObjectHandle<T>& operator=(ObjectHandle<T>&& other) = default;

    T* operator->();

private:
    T* m_value;
};

}  // namespace red

#include "inl/ObjectHandle.inl"

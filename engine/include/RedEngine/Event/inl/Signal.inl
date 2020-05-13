
#include <RedEngine/Event/Signal.hpp>

namespace red
{
// --------------- SIGNAL ---------------
template <typename... SignalArgs>
typename Signal<SignalArgs...>::Slot& Signal<SignalArgs...>::Connect(
    Signal<SignalArgs...>::Func function)
{
    m_connections.emplace_back(this, function);

    return m_connections[m_connections.size() - 1];
}

template <typename... SignalArgs>
template <class C>
typename Signal<SignalArgs...>::Slot& Signal<SignalArgs...>::Connect(
    void (C::*method)(SignalArgs... args), C* obj)
{
    auto& f = [obj, method](SignalArgs&&... funcArgs) {
        (obj->*method)(std::forward<SignalArgs>(funcArgs)...);
    };

    return Connect(std::move(f));
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Activate(bool activeValue)
{
    m_isActive = activeValue;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Deactivate()
{
    Activate(false);
}

template <typename... SignalArgs>
bool Signal<SignalArgs...>::IsActive() const
{
    return m_isActive;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::operator()(SignalArgs... args)
{
    emit(std::forward<SignalArgs>(args)...);
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::emit(SignalArgs... args)
{
    if (!m_isActive)
    {
        return;
    }

    for (auto& connection : m_connections)
    {
        if (connection.IsActive())
        {
            connection(std::forward<SignalArgs>(args)...);
        }
    }
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Disconnect(Signal::Slot& connection)
{
    //    m_connections.erase(m_connections.find(connection));
    // TODO
}

// --------------- CONNECTION ---------------
template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::Slot(Signal<SignalArgs...>* ref, Func func)
    : m_signalRef(ref), m_isActive(true), m_func(func)
{
}

template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::~Slot()
{
    m_signalRef->Disconnect(*this);
}

template <typename... SignalArgs>
bool Signal<SignalArgs...>::Slot::IsActive()
{
    return m_isActive;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Slot::Activate()
{
    m_isActive = true;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Slot::Deactivate()
{
    m_isActive = false;
}
template <typename... SignalArgs>
void Signal<SignalArgs...>::Slot::operator()(SignalArgs... args)
{
    m_func(args...);
}
}  // namespace red
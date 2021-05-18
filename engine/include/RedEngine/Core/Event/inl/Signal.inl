
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Event/Signal.hpp"

namespace red
{
// --------------- SIGNAL ---------------

template <typename... SignalArgs>
Signal<SignalArgs...>::~Signal()
{
    for (auto& connexion : m_connections)
    {
        connexion.reset();
    }
}

template <typename... SignalArgs>
typename Signal<SignalArgs...>::Slot Signal<SignalArgs...>::Connect(Signal<SignalArgs...>::Func function,
                                                                    bool keepAlive /*= false*/)
{
    int id = m_nextSlotId;
    m_nextSlotId++;

    auto connexion = std::make_shared<Connection>(this, function, id);
    if (keepAlive)
    {
        connexion->AddRef();
    }

    m_connections.push_back(std::move(connexion));

    Slot slot(m_connections.back());

    return slot;
}

template <typename... SignalArgs>
template <class C>
typename Signal<SignalArgs...>::Slot Signal<SignalArgs...>::Connect(void (C::*method)(SignalArgs... args), C* obj,
                                                                    bool keepAlive /*= false*/)
{
    auto f = [obj, method](SignalArgs&&... funcArgs) { (obj->*method)(std::forward<SignalArgs>(funcArgs)...); };

    return Connect(std::move(f), keepAlive);
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
        if (connection->IsActive())
        {
            connection->emit(std::forward<SignalArgs>(args)...);
        }
    }
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::RemoveConnection(Connection* connection)
{
    auto it = std::find_if(
        m_connections.begin(), m_connections.end(),
        [connection](const std::shared_ptr<Connection>& c) { return c->m_connectionId == connection->m_connectionId; });

    if (it != m_connections.end())
    {
        m_connections.erase(it);
    }
}

// --------------- CONNECTION ---------------
template <typename... SignalArgs>
Signal<SignalArgs...>::Connection::Connection(Signal<SignalArgs...>* ref, Func func, int slotId)
    : m_isActive(true), m_signalRef(ref), m_func(func), m_connectionId(slotId), m_refCount(0)
{
}

template <typename... SignalArgs>
Signal<SignalArgs...>::Connection::~Connection()
{
    m_isActive = false;
}

template <typename... SignalArgs>
bool Signal<SignalArgs...>::Connection::IsActive()
{
    return m_isActive;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::Activate()
{
    m_isActive = true;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::Deactivate()
{
    m_isActive = false;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::operator()(SignalArgs... args)
{
    m_func(args...);
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::emit(SignalArgs... args)
{
    m_func(args...);
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::AddRef()
{
    m_refCount++;
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Connection::RemoveRef()
{
    m_refCount--;

    if (m_refCount <= 0)
    {
        m_signalRef->RemoveConnection(this);
    }
}

// --------------- SLOT ---------------
template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::Slot(std::weak_ptr<Connection> connection) : m_connection(connection)
{
    m_connection.lock()->AddRef();
}

template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::Slot() : m_connection()
{
}

template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::~Slot()
{
    if (!m_connection.expired())
        m_connection.lock()->RemoveRef();
}

template <typename... SignalArgs>
Signal<SignalArgs...>::Slot::Slot(const Slot& other)
{
    m_connection = other.m_connection;
    if (!m_connection.expired())
        m_connection.lock()->AddRef();
}

template <typename... SignalArgs>
typename Signal<SignalArgs...>::Slot& Signal<SignalArgs...>::Slot::operator=(const Signal<SignalArgs...>::Slot& other)
{
    m_connection = other.m_connection;

    if (!m_connection.expired())
        m_connection.lock()->AddRef();

    return *this;
}

template <typename... SignalArgs>
bool Signal<SignalArgs...>::Slot::IsActive()
{
    if (m_connection.expired())
        return false;
    return m_connection.lock()->IsActive();
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Slot::Activate()
{
    if (!m_connection.expired())
        m_connection.lock()->Activate();
}

template <typename... SignalArgs>
void Signal<SignalArgs...>::Slot::Deactivate()
{
    if (!m_connection.expired())
        m_connection.lock()->Deactivate();
}

}  // namespace red
#pragma once

#include <RedEngine/Utils/Uncopyable.hpp>
#include <functional>

namespace red
{
/// The signal is the class that emit the data to the connected slots
template <typename... SignalArgs>
class Signal : public Uncopyable
{
public:
    using Func = std::function<void(SignalArgs...)>;

    class Connection : public Uncopyable
    {
        friend Signal;
        friend class Slot;

    public:
        Connection(Signal<SignalArgs...>* ref, Func m_func, int slotId);
        ~Connection();

        Connection(Connection&&) = default;
        Connection& operator=(Connection&&) = default;

        bool IsActive();

        void Activate();
        void Deactivate();

        void operator()(SignalArgs... args);

    private:
        void AddRef();
        void RemoveRef();

    private:
        bool m_isActive;
        Signal<SignalArgs...>* m_signalRef;
        Func m_func;
        int m_connectionId;
        int m_refCount;
    };

    class Slot
    {
    public:
        Slot();
        Slot(Connection* connection);
        ~Slot();

        Slot(Slot&&) = default;
        Slot& operator=(Slot&&) = default;

        Slot(const Slot&);
        Slot& operator=(const Slot&);

        bool IsActive();

        void Activate();
        void Deactivate();

    private:
        Connection* m_connection;
    };

    Signal() = default;
    ~Signal() = default;

    Signal(Signal&&) = default;
    Signal& operator=(Signal&&) = default;

    Slot Connect(Func function);
    template <class C>
    Slot Connect(void (C::*method)(SignalArgs... args), C* obj);

    void Activate(bool activeValue = true);
    void Deactivate();
    [[nodiscard]] bool IsActive() const;

    void RemoveConnection(Connection* connection);

    void operator()(SignalArgs... args);
    void emit(SignalArgs... args);

private:
    std::vector<Connection> m_connections{};
    bool m_isActive{true};
    int m_nextSlotId{0};
};

}  // namespace red

#include "inl/Signal.inl"
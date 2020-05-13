#pragma once

#include <functional>

namespace red
{
/// The signal is the class that emit the data to the connected slots
template <typename... SignalArgs>
class Signal
{
public:
    using Func = std::function<void(SignalArgs...)>;

    class Slot
    {
    public:
        Slot(Signal<SignalArgs...>* ref, Func m_func);
        ~Slot();

        bool IsActive();

        void Activate();
        void Deactivate();

        void operator()(SignalArgs... args);

    private:
        bool m_isActive;
        Signal<SignalArgs...>* m_signalRef;
        Func m_func;
    };

    Signal() = default;
    ~Signal() = default;

    Slot& Connect(Func function);
    template <class C>
    Slot& Connect(void(C::* method)(SignalArgs... args), C* obj);
    void Disconnect(Slot& connection);

    void Activate(bool activeValue = true);
    void Deactivate();
    [[nodiscard]] bool IsActive() const;

    void operator()(SignalArgs... args);
    void emit(SignalArgs... args);

private:
    std::vector<Slot> m_connections{};
    bool m_isActive{true};
};



}  // namespace red

#include "inl/Signal.inl"
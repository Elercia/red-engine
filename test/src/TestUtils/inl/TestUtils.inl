namespace red
{
void DurationCounter::Start()
{
    RedAssert(!m_isStarted, "DurationCounter is already started");
    m_start = Clock::now();
    m_isStarted = true;
}

double DurationCounter::Stop()
{
    RedAssert(m_isStarted, "DurationCounter is stopped");
    m_end = Clock::now();
    m_isStarted = false;

    return std::chrono::duration<double, std::milli>(m_end - m_start).count();
}

double DurationCounter::GetDuration()
{
    return std::chrono::duration<double, std::milli>(m_end - m_start).count();
}
}  // namespace red
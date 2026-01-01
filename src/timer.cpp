#include "timer.h"

void Timer::start()
{
    m_start_HighResolutionClock = std::chrono::high_resolution_clock::now();
    m_start_SteadyClock = std::chrono::steady_clock::now();
}

void Timer::stop()
{
    auto m_end_HighResolutionClock = std::chrono::high_resolution_clock::now();
    auto m_end_SteadyClock= std::chrono::steady_clock::now();

    time_ns_HighResolutionClock = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end_HighResolutionClock - m_start_HighResolutionClock).count();
    time_us_HighResolutionClock = std::chrono::duration_cast<std::chrono::microseconds>(m_end_HighResolutionClock - m_start_HighResolutionClock).count();

    time_ns_SteadyClock = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end_SteadyClock - m_start_SteadyClock).count();
    time_us_SteadyClock = std::chrono::duration_cast<std::chrono::microseconds>(m_end_SteadyClock - m_start_SteadyClock).count();
}

long Timer::getTimeHighResolution_us()
{
    return time_us_HighResolutionClock;
}

long Timer::getTimeHighResolution_ns()
{
    return time_ns_HighResolutionClock;
}

long Timer::getTimeSteadyClock_us()
{
    return time_us_SteadyClock;
}

long Timer::getTimeSteadyClock_ns()
{
    return time_ns_SteadyClock;
}

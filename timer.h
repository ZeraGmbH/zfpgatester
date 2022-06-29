#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();

    long getTimeHighResolution_us();
    long getTimeHighResolution_ns();
    long getTimeSteadyClock_us();
    long getTimeSteadyClock_ns();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_HighResolutionClock{};
    std::chrono::time_point<std::chrono::steady_clock> m_start_SteadyClock{};

    long time_us_HighResolutionClock{};
    long time_ns_HighResolutionClock{};
    long time_us_SteadyClock{};
    long time_ns_SteadyClock{};
};

#endif // TIMER_H

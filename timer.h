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

    long getTime_us();
    long getTime_ns();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint{};
    long time_us{};
    long time_ns{};
};

#endif // TIMER_H

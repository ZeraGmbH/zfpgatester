#include "timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::start()
{
    m_startPoint = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    auto m_endPoint = std::chrono::high_resolution_clock::now();

    time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endPoint-m_startPoint).count();
    time_us = std::chrono::duration_cast<std::chrono::microseconds>(m_endPoint-m_startPoint).count();
}

long Timer::getTime_us()
{
    return time_us;
}

long Timer::getTime_ns()
{
    return time_ns;
}

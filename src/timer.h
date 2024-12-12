#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Timer {
public:
    Timer(const std::string& label = "Timer");

    void reset();

    double elapsedMilliseconds() const;

    double elapsedMicroseconds() const;

    double elapsedSeconds() const;

    void printElapsed() const;

private:
    std::string m_Label;
    std::chrono::high_resolution_clock::time_point m_StartTime;
};

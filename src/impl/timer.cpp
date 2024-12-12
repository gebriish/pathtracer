#include "../timer.h"


Timer::Timer(const std::string& label)
  : m_Label(label), m_StartTime(std::chrono::high_resolution_clock::now()) 
{}


void Timer::reset() {
  m_StartTime = std::chrono::high_resolution_clock::now();
}

double Timer::elapsedMilliseconds() const {
  return std::chrono::duration<double, std::milli>(
      std::chrono::high_resolution_clock::now() - m_StartTime
      ).count();
}

double Timer::elapsedMicroseconds() const {
  return std::chrono::duration<double, std::micro>(
      std::chrono::high_resolution_clock::now() - m_StartTime
      ).count();
}

double Timer::elapsedSeconds() const {
  return std::chrono::duration<double>(
      std::chrono::high_resolution_clock::now() - m_StartTime
      ).count();
}

void Timer::printElapsed() const {
  std::cout << m_Label << " - Elapsed time: "
    << elapsedMilliseconds() << " ms\n";
}

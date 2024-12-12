#include "Timer.h"

Timer::Timer()
	: m_startTime{ std::chrono::steady_clock::now() }
{
	/*EMPTY*/
}

void Timer::Restart()
{
	m_startTime = std::chrono::steady_clock::now();
}

float Timer::GetElapsedTime()
{
	std::chrono::duration<float> elapsedTime = std::chrono::steady_clock::now() - m_startTime;
	return elapsedTime.count();
}

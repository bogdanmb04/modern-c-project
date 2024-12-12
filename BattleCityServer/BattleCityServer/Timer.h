#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	void Restart();
	float GetElapsedTime();
private:
	std::chrono::steady_clock::time_point m_startTime;
};
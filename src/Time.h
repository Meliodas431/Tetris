#pragma once
#include <time.h>
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <chrono>
#include <ratio>
#include <functional>
class Timer {
public:
	float m_delay{ 0.3f };
 uint16_t m_holdDelay{ 59 };
	float m_gameTiming{ 0 };
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoind;
	static Timer instance;
public:
	Timer();
	void reset();
  float stop();
std::pair<bool, uint16_t> printTimer();
  static Timer* get();
};
#include "time.h"
#include "game.h"

Timer Timer::instance;

 void Timer::reset() {
	 mTimePoint = std::chrono::high_resolution_clock::now(); 
 }

float Timer::stop() { 
	auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(mTimePoint).time_since_epoch().count();
	endTimePoind = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoind).time_since_epoch().count();
	auto ms = end - start;
	auto fp_ms = ms * 0.001;

	return fp_ms;
}

Timer::Timer() {
	get();
	reset();
}

Timer* Timer::get() {
	return &instance;
}

std::pair<bool, uint16_t> Timer::printTimer() {
	static auto start= std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration<float>(end - start);

	bool done = false;
	if (elapsed.count() >= 1.f) {
		start = std::chrono::high_resolution_clock::now();
	    m_holdDelay--;
		if (m_holdDelay == 0) {
			m_holdDelay = 59;
			done = true;
		}
	}
	return { done,  m_holdDelay };
}
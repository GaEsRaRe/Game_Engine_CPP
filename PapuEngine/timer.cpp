#include "timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start() {
	_start = std::clock();
	_running = true;
	_finished = false;
}

void Timer::run() {
	if (_running) {
		if (get_time() >= _duration) {
			_finished = true;
			_running = false;
		}
	}
}
float Timer::get_time() {
	if (_running) {
		return float((std::clock() - _start)/1000.000f);
		
	}
	else {
		return 0.000f;
	}
	
}
bool Timer::is_finished() {
	return _finished;
}
void Timer::set_duration(float duration) {
	_duration = duration;
}
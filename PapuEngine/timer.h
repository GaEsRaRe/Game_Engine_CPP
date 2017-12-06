#pragma once
#include <iostream>
#include <cstdio>
#include <ctime>


using namespace std;

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	float get_time();
	bool is_finished();
	void set_duration(float duration);
	void run();
private:
	bool _running;
	bool _finished;
	std::clock_t _start;
	double _duration;
};


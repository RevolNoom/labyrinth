#include "Timer.h"

Timer::Timer(float seconds): 
	_timeLeft(seconds), 
	_timeMax(seconds), 
	_pause(true)
{
}

void Timer::Update(float delta)
{
	if (_pause)
		return;

	_timeLeft -= delta;
	if (_timeLeft < 0)
	{
		_timeLeft = 0;
		Pause();
	}
}

void Timer::Start()
{
	if (IsPausing())
	{
		Reset();
		_pause = false;
	}
}

void Timer::SetTime(float seconds)
{
	_timeMax = seconds;
	_timeLeft = _timeMax;
	_pause = true;
}

void Timer::Pause()
{
	_pause = true;
}

void Timer::Reset()
{
	_timeLeft = _timeMax;
	_pause = true;
}

float Timer::TimeLeft()
{
	return _timeLeft;
}

bool Timer::IsPausing()
{
	return _pause;
}

bool Timer::TimeOut()
{
	return _timeLeft <= 0;
}

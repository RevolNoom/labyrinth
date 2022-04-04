#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer(float seconds);

	void Update(float delta);

	// Make the timer starts counting down
	// Restart the timer if it has count off.
	void Start();

	// Pause the timer
	// Set the timer's value to this value 
	void SetTime(float seconds);

	// Stop the timer from counting down.
	void Pause();

	// Set the counter back to initial value
	// and pause it.
	void Reset();

	float TimeLeft();

	bool IsPausing();
	bool TimeOut();

private:
	float _timeLeft;
	float _timeMax;
	bool _pause;
};

#endif // TIMER_H
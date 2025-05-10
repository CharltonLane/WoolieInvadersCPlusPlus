#pragma once
class Timer
{
	// Flexible timer class.
	// Timers have a duration and will always tick down towards 0.

public:
	Timer(float startingDuration, bool startPaused = false)
		: m_durationSeconds{ startingDuration }
		, m_remainingSeconds{ startingDuration }
		, m_isPaused{ startPaused }
	{}

	Timer(float durationSeconds, float startingSeconds, bool startPaused = false)
		: m_durationSeconds{ durationSeconds }
		, m_remainingSeconds{ startingSeconds }
		, m_isPaused{ startPaused }
	{}

	void Tick(float dt);
	void Pause();
	void Unpause();

	float GetTimeRemaining() const;
	bool HasTimerLapsed() const;

	void Restart();
	void AddTime(float secondsToAdd);
	void SetTimerOneShot(float remainingSeconds);
	void SetDuration(float durationSeconds);


private:
	float m_durationSeconds{}; // The standard duration of the timer.
	float m_remainingSeconds{};
	bool m_isPaused{ false };
};


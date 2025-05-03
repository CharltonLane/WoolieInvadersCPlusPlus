#pragma once
class Timer
{
private:
	float m_remainingSeconds{};
	float m_startingSeconds{};
	bool m_isPaused{ false };

public:
	Timer(float startingDuration, bool startPaused = false)
		: m_startingSeconds{ startingDuration }
		, m_remainingSeconds{ startingDuration }
		, m_isPaused{ startPaused }
	{}

	void SetTimer(float newValue);
	void Tick(float dt);
	float GetTimeRemaining() const;
	void Pause();
	void Unpause();
	bool HasTimerLapsed() const;
};


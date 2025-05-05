#include "timer.h"

void Timer::SetTimer(float newValue) {
	m_remainingSeconds = newValue;
}

void Timer::Tick(float dt) {
	if (m_isPaused) {
		return;
	}
	m_remainingSeconds -= dt;
}

float Timer::GetTimeRemaining() const {
	return m_remainingSeconds;
}

void Timer::Pause() {
	m_isPaused = true;
}

void Timer::Unpause() {
	m_isPaused = false;
}

bool Timer::HasTimerLapsed() const {
	return m_remainingSeconds <= 0.0f;
}

void Timer::Restart() {
	m_remainingSeconds = m_startingSeconds;
}

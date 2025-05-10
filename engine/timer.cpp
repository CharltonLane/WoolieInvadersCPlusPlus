#include "timer.h"

void Timer::SetTimerOneShot(float remainingSeconds) {
	// Can be used to set the remaining time above the timer's usual duration.
	m_remainingSeconds = remainingSeconds;
}

void Timer::SetDuration(float durationSeconds) {
	m_durationSeconds = durationSeconds;
}

void Timer::AddTime(float secondsToAdd) {
	// Can be used to set the remaining time above the timer's usual duration.
	m_remainingSeconds += secondsToAdd;
}

void Timer::Tick(float dt) {
	if (m_isPaused) {
		return;
	}
	if (m_remainingSeconds <= 0.0f) {
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
	m_remainingSeconds = m_durationSeconds;
}

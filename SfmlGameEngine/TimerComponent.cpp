#include "pch.h"
#include "TimerComponent.h"
#include <cassert>

TimerComponent::TimerComponent(float ms, bool repeat) : m_Interval(ms / 1000), m_Repeat(repeat) {
	Show(false);
}

void TimerComponent::SetInterval(float ms, bool repeat) {
	m_Interval = ms / 1000;
	m_Repeat = repeat;
}

float TimerComponent::GetInterval() const {
	return m_Interval * 1000;
}

bool TimerComponent::IsRepeating() const {
	return m_Repeat;
}

void TimerComponent::Start() {
	Enable(true);
}

void TimerComponent::Stop() {
	Enable(false);
}

void TimerComponent::Enable(bool enable) {
	GameComponent::Enable(enable);
	if (enable)
		m_Current = 0;
}

float TimerComponent::GetTime() const {
	return m_Current * 1000;
}

void TimerComponent::Update(float dt) {
	assert(IsEnabled());
	if ((m_Current += dt) >= m_Interval) {
		OnTick();
		m_Current -= m_Interval;
		if (!m_Repeat)
			Stop();
	}
}

void TimerComponent::OnTick() {
	if (Tick)
		Tick(*this);
}

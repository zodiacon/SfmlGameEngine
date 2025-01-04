#pragma once

#include <functional>
#include "GameComponent.h"

class TimerComponent : public GameComponent {
public:
	explicit TimerComponent(float intervalInMsec = 0, bool repeat = false);
	void SetInterval(float intervalInMsec, bool repeat = false);
	float GetInterval() const;
	bool IsRepeating() const;

	void Start();
	void Stop();
	void Enable(bool enable) override;
	float GetTime() const;

	void Update(float dt) override;

	std::function<void(TimerComponent&)> Tick;

protected:
	virtual void OnTick();

private:
	float m_Interval;
	float m_Current{ 0 };
	bool m_Repeat;
};


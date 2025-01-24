#include "timer.h"

void InitTimer(Timer* _timer, float _maxValue)
{
	_timer->current = 0;
	_timer->max = _maxValue;
}

void UpdateTimer(float _dt, Timer* _timer)
{
	_timer->current += _dt;
}

sfBool IsTimerFinished(Timer* _timer)
{
	if (_timer->current > _timer->max)
	{
		_timer->current = 0;
		return sfTrue;
	}
	return sfFalse;
}
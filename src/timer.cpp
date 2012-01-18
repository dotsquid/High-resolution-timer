#include "timer.h"

Timer::Timer(bool _start):
	startTick(0UL),	
	prevElapsedTime(0LL),
	period(0UL),
	started(false)
{
	startTime.QuadPart = 0LL;
	clockFrequency.QuadPart = 0LL;
	QueryPerformanceFrequency(&clockFrequency);
	Reset(_start);
}

void Timer::Reset(bool _start)
{
	QueryPerformanceCounter(&startTime);
	startTick = GetTickCount();
	prevElapsedTime = 0;
	started = _start;
}

void Timer::SetPeriod(ULONG _period)
{
	period = _period;
}

ULONG Timer::GetPeriod()
{
	return period;
}

void Timer::Start()
{
	started = true;
}

void Timer::Stop()
{
	started = false;
}

ULONG Timer::GetUSec(bool _reset)
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	LONGLONG elapsedTime = currentTime.QuadPart - startTime.QuadPart;

	// Compute the number of millisecond ticks elapsed.
	unsigned long msTicks = (unsigned long)(1000 * elapsedTime / clockFrequency.QuadPart);

	// Check for unexpected leaps in the Win32 performance counter.  
	// (This is caused by unexpected data across the PCI to ISA 
	// bridge, aka south bridge.  See Microsoft KB274323.)
	unsigned long elapsedTicks = GetTickCount() - startTick;
	signed long msOff = (signed long)(msTicks - elapsedTicks);
	if (msOff < -100 || msOff > 100)
	{
		// Adjust the starting time forwards.
		LONGLONG msAdjustment = tmin(msOff * clockFrequency.QuadPart / 1000, elapsedTime - prevElapsedTime);
		startTime.QuadPart += msAdjustment;
		elapsedTime -= msAdjustment;
	}

	// Store the current elapsed time for adjustments next time.
	prevElapsedTime = elapsedTime;

	// Convert to microseconds.
	unsigned long usTicks = (unsigned long)(1000000 * elapsedTime / clockFrequency.QuadPart);

	if (_reset)
	{
		Reset(started);
	}

	return usTicks;
}

ULONG Timer::GetMSec(bool _reset)
{
	return GetUSec(_reset) / 1000;
}

float Timer::GetMSecF(bool _reset)
{
	return static_cast<float>(GetUSec(_reset)) / 1000.0f;
}

float Timer::GetSec(bool _reset)
{
	return static_cast<float>(GetUSec(_reset)) / 1000000.0f;
}

bool Timer::OnTimer()
{
	if(started)
	{
		if(GetUSec() >= period)
		{
			Reset(started);
			return true;
		}
	}
	return false;
}
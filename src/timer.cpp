#include "timer.h"

Timer::Timer(bool _start):
    data(),
    period(0UL),
	started(false)
{

#if defined(WIN32) || defined(_WIN32)
    data.startTime.QuadPart = 0LL;
    data.clockFrequency.QuadPart = 0LL;
    QueryPerformanceFrequency(&data.clockFrequency);
#else
#endif //WIN32

	Reset(_start);
}

void Timer::Reset(bool _start)
{

#if defined(WIN32) || defined(_WIN32)
    QueryPerformanceCounter(&data.startTime);
    data.startTick = GetTickCount();
    data.prevElapsedTime = 0;
#else
    gettimeofday(&data.startTime, NULL);
#endif //WIN32
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
#if defined(WIN32) || defined(_WIN32)
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
    LONGLONG elapsedTime = currentTime.QuadPart - data.startTime.QuadPart;

	// Compute the number of millisecond ticks elapsed.
    unsigned long msTicks = (unsigned long)(1000 * elapsedTime / data.clockFrequency.QuadPart);

	// Check for unexpected leaps in the Win32 performance counter.  
	// (This is caused by unexpected data across the PCI to ISA 
	// bridge, aka south bridge.  See Microsoft KB274323.)
    unsigned long elapsedTicks = GetTickCount() - data.startTick;
	signed long msOff = (signed long)(msTicks - elapsedTicks);
	if (msOff < -100 || msOff > 100)
	{
		// Adjust the starting time forwards.
        LONGLONG msAdjustment = tmin(msOff * data.clockFrequency.QuadPart / 1000, elapsedTime - data.prevElapsedTime);
        data.startTime.QuadPart += msAdjustment;
		elapsedTime -= msAdjustment;
	}

	// Store the current elapsed time for adjustments next time.
    data.prevElapsedTime = elapsedTime;

	// Convert to microseconds.
    ULONG usec = (ULONG)(1e06 * elapsedTime / data.clockFrequency.QuadPart);
#else
    ULONG usec;
    timeval currentTime, diff;
    gettimeofday(&currentTime, NULL);
    timersub(&currentTime, &data.startTime, &diff);
    usec = (ULONG)diff.tv_sec * 1e06 + diff.tv_usec;
#endif //WIN32

    if (_reset)
    {
        Reset(started);
    }

    return usec;
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

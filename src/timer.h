/**************************************************************
//   
//   timer.h
//   XorsTeam
//   Kyrylo 'dotsquid' Iakovliev
//   Copyright (c) 09/15/2011 All Right Reserved
//   
//   Timer class inspired by btClock from Bullet Physics.
//   Microsecond resolution.
//   
**************************************************************/


#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>
#include <time.h>

#define tmin(a,b) (a > b ? a : b)

class Timer
{
    private:
        LARGE_INTEGER clockFrequency;
        DWORD startTick;
        LONGLONG prevElapsedTime;
        LARGE_INTEGER startTime;
        ULONG period;
        bool started;
    public:
        Timer(bool _start = false);
        ~Timer(){}
        void Start();
        void Stop();
        void Reset(bool _start = false);
        void SetPeriod(ULONG period);
        ULONG GetUSec(bool _reset = false);
        ULONG GetMSec(bool _reset = false);
		float GetMSecF(bool _reset = false);
        float GetSec(bool _reset = false);
        bool OnTimer();
};

#endif
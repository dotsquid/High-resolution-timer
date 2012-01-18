/**************************************************************
//   
//   timer.h
//   Kyrylo 'dotsquid' Iakovliev
//   Copyright (c) 09/15/2011
//   
//   Timer class inspired by btClock from Bullet Physics.
//   Microsecond resolution.
//   
**************************************************************/


#ifndef _TIMER_H_
#define _TIMER_H_

#if defined(WIN32) || defined(_WIN32)
	#include <windows.h>
	#include <time.h>
#else // WIN32
#endif // WIN32

#define tmin(a,b) (a > b ? a : b)

/*!
	\brief Timer with microsecond resolution.
	\details <b>Currently Win32 only.</b>\n
	Based on QueryPerformanceCounter routine.
*/
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

		/*!
			\brief Contructor.
			\param _start If true, then timer is started immediately.
		*/
        Timer(bool _start = false);

		/*!
			\brief Default destructor.
		*/
        ~Timer(){}

		/*!
			\brief Starts the timer.
			\details If timer is started, then \ref OnTimer method can be used.\n
			Nevertheless, the time passed since the start or reset can be received anyway.
		*/
        void Start();

		/*!
			\brief Stops the timer.
			\details See \ref Start for more details.
		*/
        void Stop();

		/*!
			\brief Resets the timer.
			\details See \ref Start for more details.
			\param _start If true, restarts the timer.
		*/
        void Reset(bool _start = false);

		/*!
			\brief Sets the period of the timer.
			\details See \ref OnTimer for more details.
			\param period Timer period.
		*/
        void SetPeriod(ULONG period);

		/*!
			\brief Returns the period of the timer.
		*/
		ULONG GetPeriod();

		/*!
			\brief Returns the time in microseconds passed since the last reset.
			\param _reset If true, resets the timer.
		*/
        ULONG GetUSec(bool _reset = false);

		/*!
			\brief Returns the time in milliseconds passed since the last reset.
			\param _reset If true, resets the timer.
		*/
        ULONG GetMSec(bool _reset = false);

		/*!
			\brief Returns the time in milliseconds (as a float with microseconds in the fractional part) passed since the last reset.
			\param _reset If true, resets the timer.
		*/
		float GetMSecF(bool _reset = false);

		/*!
			\brief Returns the time in seconds passed since the last reset.
			\param _reset If true, resets the timer.
		*/
        float GetSec(bool _reset = false);

		/*!
			\brief Returns true if the time passed since last reset exceeds the period value.			
		*/
        bool OnTimer();
};

#endif
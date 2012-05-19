#include <iostream>

#if defined(WIN32) || defined(_WIN32)
#else
    #include <unistd.h>
#endif // WIN32

#include "../src/timer.cpp"

void halt(unsigned int msecs)
{
#if defined(WIN32) || defined(_WIN32)
	Sleep(msecs);
#else // WIN32
	usleep(msecs * 1000);
#endif // WIN32
}

using namespace std;

float bar(const int N = 10000)
{
    float p = 1.0f;
    for (int j = 1; j < N+1; ++j)
    {
        p *= 1.0f + (float)j / float(N);
    }
    return p;
}

float foo(const int N = 10000)
{
    float s = .0f;
    for (int i = 0; i < N; ++i)
    {
        float p = bar(N);
        s += p;
    }
    return s;
}

int main()
{
	Timer timer;

	// starting the timer, waiting for 1 second and reading the timer
	timer.Start();
	halt(1000);
	cout << timer.GetUSec() << " us" << endl;

    //
    for (int i = 0; i < 10; ++i)
    {
        timer.Reset();
        float f = foo();
        cout << "[" << i+1 << "] (" << f << ") " << timer.GetUSec() << " us" << endl;
    }

	// every second read the timer
    timer.Reset(true);
	timer.SetPeriod((ULONG)1E+06);
	for (int i = 0; i < 5;)
	{
		if(timer.OnTimer())
		{
			cout << "[" << i++ << "]  Hell, it's about time!" << endl;
		}
	}

	return 0;
}

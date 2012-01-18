#include <iostream>
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

int main()
{
	Timer timer;

	// starting the timer, waiting for 1 second and reading the timer
	timer.Start();
	halt(1000);
	cout << timer.GetUSec() << " us" << endl;

	// every second read the timer
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
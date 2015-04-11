#include "TimeManager.h"

#include <chrono>
using namespace std::chrono;



double TimeManager::CalculateFrameRate(bool write = false) {

	static double FramesPerSecond = 0.0f;
	static double StartTime = GetTime();
	static double LastTime = GetTime();
	static char strFrameRate[50] = { 0 };
	static double CurrentFPS = 0.0f;


	CurrentTime = GetTime();


	DeltaTime = CurrentTime - LastTime;

	LastTime = CurrentTime;

	++FramesPerSecond;


	if (CurrentTime - StartTime > 1.0f) {
		
		StartTime = CurrentTime;

		if (write)
			fprintf(stderr, "Current Frames Per Second: %d\n", int(FramesPerSecond));

		CurrentFPS = FramesPerSecond;

		FramesPerSecond = 0;
	}

	return CurrentFPS;
}

double TimeManager::GetTime() {

	// Get the current system since since the epoch
	auto BeginningOfTime = std::chrono::system_clock::now().time_since_epoch();

	// Convert the system time to milliseconds
	auto ms = duration_cast<milliseconds>(BeginningOfTime).count();

	// Return system time, and give a fractional value
	return ms * 0.001;
}


void TimeManager::Sleep(int ms) {

	std::this_thread::sleep_for(milliseconds(ms));
}


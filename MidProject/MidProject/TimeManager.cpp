#include "TimeManager.h"

#include <chrono>
using namespace std::chrono;



// Calculates our current frames per second and displays it
double TimeManager::CalculateFrameRate(bool write = false) {

	static double FramesPerSecond = 0.0f;		// Stores FPS
	static double StartTime = GetTime();		// Time per second to test
	static double LastTime = GetTime();			// Hold the time from last frame
	static char strFrameRate[50] = { 0 };		// String for Window Title
	static double CurrentFPS = 0.0f;			// Holds the current FPS

	// Get the current time in seconds
	CurrentTime = GetTime();

	// Calculate delta time - Time elapsed since last time we checked time
	DeltaTime = CurrentTime - LastTime;

	// Store lastTime as currentTime
	LastTime = CurrentTime;

	// Increase FrameCounter
	++FramesPerSecond;

	// If a second has passed - Get current Frame rate
	if (CurrentTime - StartTime > 1.0f) {
		
		// Set start time to the currenttime - used as a starting point for next second
		StartTime = CurrentTime;

		// Show the FPS to the console
		if (write)
			fprintf(stderr, "FPS: %d\n", int(FramesPerSecond));

		// Store the current FPS since we reset it
		CurrentFPS = FramesPerSecond;
		
		// Reset FPS
		FramesPerSecond = 0;
	}

	// Return most recent FPS
	return CurrentFPS;
}


// Returns the current time in seconds
double TimeManager::GetTime() {

	// Get the current system since since the epoch
	auto BeginningOfTime = std::chrono::system_clock::now().time_since_epoch();

	// Convert the system time to milliseconds
	auto ms = duration_cast<milliseconds>(BeginningOfTime).count();

	// Return system time, and give a fractional value
	return ms * 0.001;
}


// Pauses the current thread for an amount of time in milliseconds
void TimeManager::Sleep(int ms) {

	// Use the sleep_for() function to pause the current thread
	std::this_thread::sleep_for(milliseconds(ms));
}


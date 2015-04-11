#ifndef TIMEMANAGER_H_
#define TIMEMANAGER_H_

#include <chrono>
#include <thread>

// TimeManager class to calculate frame rate and give a time slice
// 
class TimeManager {
	
public:

	// Function used to get the instance of the manager, or initialize and return the instance
	// By creating a static variable of the instance we ensure this only gets created once
	static TimeManager& Instance() {

		static TimeManager instance;

		return instance;
	}

	// This calculate our current frames per second
	double CalculateFrameRate(bool writeToConsole);

	// Returns current time in seconds
	double TimeManager::GetTime();

	// Pauses the current thread for an amount of time
	void Sleep(int milliseconds);

	// The time slice that stores the total time in seconds elapsed since last frame
	double DeltaTime = 0;

	// Current time in seconds
	double CurrentTime = 0;

private:
	TimeManager() {}							 // Private constructor -- Cannot be called
	TimeManager(TimeManager const&);			 // Copy constructor is private
	TimeManager& operator=(TimeManager const&);  // Assignment operator is private
};

#endif
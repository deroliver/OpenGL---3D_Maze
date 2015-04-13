#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <string>
#include <fstream>
#include "InputManager.h"


// Class to manage creation of the window, input, and creating OpenGL context.
// This class is inherited from for specific implementations (GLFWManager)
class WindowManager {

public:

	// Needed so the inheriting class will have its destructor called
	virtual ~WindowManager() {}

	// Initializes the window and creates the OpenGL context
	virtual int Initialize(int width, int height, std::string Title, bool FullScreen = false) = 0;

	// Swaps the backbuffer to the front - Is called every frame
	virtual void SwapTheBuffers() = 0;

	// Processes all the input for our application
	virtual bool ProcessInput(bool continueGame) = 0;

	// Destroys the window and OpenGL context
	virtual void Destroy() = 0;

	// A way to access our application's InputManager
	virtual InputManager *GetInputManager() { return &InputManager; }

protected:

	// Variable to an input manager to control the Camera movement
	InputManager InputManager;
};

#endif
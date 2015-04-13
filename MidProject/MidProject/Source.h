#ifndef SOURCE_H_
#define SOURCE_H_

#include "Camera.h"
#include "WindowManager.h"
#include "MazeBlocks.h"

// Source application class controls the initializing, game loop, and destroying of all objects
class Source {

public:
	// Width and height of the screen
	static const int ScreenWidth = 1366;
	static const int ScreenHeight = 768;

	// Create a default constructor and deconstructor which cleans up
	Source() {}
	~Source() { Destroy(); }

	// Main function - This is called by the main() function in WindowManager
	// Abstracts the entry point
	int Main();

	// Gettter and setter for the WindowManager
	WindowManager *GetWindowManager() { return WindowManager; }
	void SetWindowManager(WindowManager *WM) { WindowManager = WM; }

	// Getter and setter for the Camera
	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *C) { Camera = C; }

	// Initializes the application
	void Initialize();

	// Runs the game loop, only quits when the user presses escape or closes the window
	void GameLoop();

	// Cleans up the application, tells all the other objects to Destroy too
	void Destroy();

	// Checks collision between a vec3 and a Rec object
	bool CheckCollision(vec3 Cam, Rec Rect);

protected:

	// Abstract window manager used to create the window and manage input
	// This is instantiated and set in GLFWManager in the main() function
	WindowManager *WindowManager;

	// The Camera for our application
	Camera *Camera;
};

#endif
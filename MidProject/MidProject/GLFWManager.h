#ifndef GLFWMANAGER_H_
#define GLFWMANAGER_H_
#define GLM_FORCE_RADIANS	

#include <string>
#include <fstream>
#include "GLFW\glfw3.h"
#include "WindowManager.h"


class GLFWManager : public WindowManager {

public:

	// Create empty constructor and have the destructor release memory
	GLFWManager() { }
	~GLFWManager() { Destroy(); }

	// Initializes the window and created the OpenGL context
	virtual int Initialize(int width, int height, std::string Title, bool Full = false) override;

	// Swaps the backbuffer to the front -- Is called every frame
	virtual void SwapTheBuffers() override;

	// Processes any needed input for the application
	virtual bool ProcessInput(bool ContinueGame) override;

	// Destroys the window and OpenGL context
	virtual void Destroy();

protected:

	// The GLFW window object
	GLFWwindow* Window;
};

#endif
#include "GLFWManager.h"


int main() {

	GLFWManager *pWM = new GLFWManager;

	Camera *pCam = new Camera();


	Source source;
	source.SetWindowManager(pWM);

	source.SetCamera(pCam);
	pWM->GetInputManager()->SetCamera(pCam);


	return source.Main();
}


int GLFWManager::Initialize(int W, int H, std::string Title, bool Full) {

	// Tries to init the GLFW library and make sure its available
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Tells OpenGL we want multi-sampling value of 4 -- Or anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Set our current OpenGL version to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window either in full screen or not
	if (Full)
		Window = glfwCreateWindow(W, H, Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		Window = glfwCreateWindow(W, H, Title.c_str(), nullptr, nullptr);


	if (Window == nullptr) {
		fprintf(stderr, "Failed to create a GLFW window\n");
		Destroy();

		return -1;
	}

	// Create OpenGl context from the window and specified settings
	glfwMakeContextCurrent(Window);

	// Turns on STICKY_KEYS for the keyboard input
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);

	// Want to be able to hide the mouse
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the cursor position to be in the top left corner
	// Now we can get the delta of the mouse position from (0, 0) and reset it again
	glfwGetCursorPos(Window, 0, 0);

	// Turns off vertical sync
	glfwSwapInterval(0);

	// Tell glew to grab all OpenGL functions/extensions even if "experimental"
	glewExperimental = GL_TRUE;

	// Initialize the GLEW libary and attach OpenGL functions and extensions
	GLenum err = glewInit();

	// If there was an error
	if (GLEW_OK != err) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Return 0 - Successfull
	return 0;
}


// Swaps the back buffer to the front buffer to display the content rendered
void GLFWManager::SwapTheBuffers() {
	
	// Takes the Window and swaps back buffer to the front
	glfwSwapBuffers(Window);
}


bool GLFWManager::ProcessInput(bool Continue = true) {

	// Check for the user pressing the escape key, as well as window close event
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Window) != 0)
		return false;


	if (glfwGetKey(Window, GLFW_KEY_UP) || glfwGetKey(Window, GLFW_KEY_W))
		InputManager.KeyPressed(InputCode::Up);

	if (glfwGetKey(Window, GLFW_KEY_DOWN) || glfwGetKey(Window, GLFW_KEY_S))
		InputManager.KeyPressed(InputCode::Down);

	if (glfwGetKey(Window, GLFW_KEY_LEFT) || glfwGetKey(Window, GLFW_KEY_A))
		InputManager.KeyPressed(InputCode::Left);

	if (glfwGetKey(Window, GLFW_KEY_RIGHT) || glfwGetKey(Window, GLFW_KEY_D))
		InputManager.KeyPressed(InputCode::Right);

	// Variable to store current mouse pos
	double mouseX, mouseY;

	// Get current mouse pos from our window
	glfwGetCursorPos(Window, &mouseX, &mouseY);

	// If mouse moved, send to input manager, which tells the camera
	if (mouseX != 0 && mouseY != 0) {
		
		// Send updated mouse position to InputManager
		InputManager.MouseMoved((float)mouseX, (float)mouseY);
	}

	// Reset the mouse position to (0, 0)
	glfwSetCursorPos(Window, 0, 0);

	// Poll input events to see if user quit or closed the window
	glfwPollEvents();

	// Return the value passed to tell teh game loop if we should continue or not
	return Continue;
}


void GLFWManager::Destroy() {
	
	// Closes OpenGL window and terminates the application
	glfwTerminate();
}
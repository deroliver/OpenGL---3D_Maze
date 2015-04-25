#include <iostream>
#include "WindowManager.h"
#include "GL\glew.h"
#include "GraphicsObject.h"
#include "Source.h"
#include "TimeManager.h"
#include "Ground.h"
#include "MazeBlocks.h"
#include "Skybox.h"

SkyBox Skybox(36);		// Skybox object
Ground Ground_1(2166);	// Ground object
MazeBlocks Maze(16000);	// Maze object


// Main() function that abstracts the required main function
int Source::Main() {

	// Calls the Initialize function below
	Initialize();

	// Calls the GameLoop function - runs until the window is closed or escape is pressed
	GameLoop();

	// Cleans up
	Destroy();

	return 0;
}


// Initializes the window, shaders, and objects
void Source::Initialize() {

	// Makes sure the WindowManager is initializes
	if (!WindowManager || WindowManager->Initialize(ScreenWidth, ScreenHeight, "MidTerm Project", false) != 0) {

		exit(-1);
	}

	// Tell OpenGl we want a 3D viewport the same size as the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Tells OpenGl we want depth testing so it renders the order correctly
	glEnable(GL_DEPTH_TEST);

	// Initialize all of our objects using the specificed shaders
	Maze.Initialize(Maze.vertices, 16000, "Shaders/Shader.VertText", "Shaders/Shader.FragText");
	Skybox.Initialize(Skybox.vertices, 36, "Shaders/Shader.VertNorm", "Shaders/Shader.FragNorm");
	Ground_1.Initialize(Ground_1.vertices, 2166, "Shaders/Shader.VertText", "Shaders/Shader.FragText");
	

	// Create the projection matrix for our camera and make the near field closer and the far field farther
	Camera->SetPersepective(radians(75.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	// Set the camera position
	Camera->PositionCamera(-69, 95, -22, 0, 0);

	// Set the camera for our skybox
	Skybox.SetCamera(Camera);
	// Set Skybox position
	Skybox.SetPosition(vec3(0, 75, 0));

	// Set the camera for our skybox
	Maze.SetCamera(Camera);
	// Set maze position
	Maze.SetPosition(vec3(-65, 0, -65));

	
	for (int i = 0; i < Maze.Rects.size(); i++) {
		Maze.Rects.at(i).X += (-65);
		Maze.Rects.at(i).Z += (-65);
	}
	

	// Set the camera for our skybox
	Ground_1.SetCamera(Camera);
	// Set ground position
	Ground_1.SetPosition(vec3(0, 0, 0));
}

// Checks collision between a vec3 and a Rec object
bool Source::CheckCollision(vec3 Cam, Rec Rect) {
	if (glm::abs(Cam.x - Rect.X) < 2.0 + Rect.GetSizeX()) {

		if (glm::abs(Cam.y - Rect.Y) < 5.0 + Rect.GetSizeY()) {

			if (glm::abs(Cam.z - Rect.Z) < 2.0 + Rect.GetSizeZ()) {
				return true;
			}
		}	
	}
	return false;
}


void Source::GameLoop() {
	// Processes input, and displays the frame rate
	while (WindowManager->ProcessInput(true)) {
		for (int i = 0; i < Maze.Rects.size(); i++) {
			if (CheckCollision(Camera->GetPosition(), Maze.Rects.at(i))) {
				//Camera->SetPosition
			}
		}

		// Use the TimeManager to calculate the framerate
		TimeManager::Instance().CalculateFrameRate(true);

		// Clear the buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render all of our objects
		Skybox.Render();
		Ground_1.Render();
		Maze.Render();

		// Tell the thread to sleep - Slowing down the program
		TimeManager::Instance().Sleep(10);

		// Swap the buffers
		WindowManager->SwapTheBuffers();
	}
}


// Used to cleanup the application
void Source::Destroy() {

	// Destroy our objects
	Ground_1.Destroy();
	Maze.Destroy();
	Skybox.Destroy();

	// If there is still a WindowManager - Destroy it
	if (WindowManager) {
		WindowManager->Destroy();

		delete WindowManager;
		WindowManager = nullptr;
	}

	// If there is still a camera - Destroy it
	if (Camera) {
		delete Camera;
		Camera = nullptr;
	}
}
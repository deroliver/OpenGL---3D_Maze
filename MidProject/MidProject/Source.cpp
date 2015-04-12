#include <iostream>

#include "GL\glew.h"
#include "GraphicsObject.h"
#include "Source.h"
#include "TimeManager.h"
#include "Ground.h"
#include "MazeBlocks.h"
#include "Skybox.h"

SkyBox Skybox(200);
Ground Ground_1(486);
MazeBlocks Maze(16000);


int Source::Main() {

	Initialize();

	GameLoop();

	Destroy();

	return 0;
}

void Source::Initialize() {

	if (!WindowManager || WindowManager->Initialize(ScreenWidth, ScreenHeight, "MidTerm Project", false) != 0) {

		exit(-1);
	}

	// Tell OpenGl we want a 3D viewport the same size as the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Tells OpenGl we want depth testing so it renders the order correctly
	glEnable(GL_DEPTH_TEST);

	Skybox.Initialize(Skybox.vertices, 200, "Shaders/Shader.VertNorm", "Shaders/Shader.FragNorm");
	Ground_1.Initialize(Ground_1.vertices, 486, "Shaders/Shader.VertText", "Shaders/Shader.FragText");
	Maze.Initialize(Maze.vertices, 16000, "Shaders/Shader.VertNorm", "Shaders/Shader.FragNorm");



	// Create the projection matrix for our camera and make the near field closer and the far field farther
	Camera->SetPersepective(radians(75.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	Camera->PositionCamera(0, 50, -10, 0, 0);

	Skybox.SetCamera(Camera);
	Skybox.SetPosition(vec3(0, 75, 0));

	Maze.SetCamera(Camera);
	Maze.SetPosition(vec3(-7, 0, -7));

	Ground_1.SetCamera(Camera);
	Ground_1.SetPosition(vec3(0, 0, 0));
}



void Source::GameLoop() {

	while (WindowManager->ProcessInput(true)) {
		TimeManager::Instance().CalculateFrameRate(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Skybox.Render();
		Ground_1.Render();
		Maze.Render();

		TimeManager::Instance().Sleep(10);

		WindowManager->SwapTheBuffers();
	}
}


void Source::Destroy() {

	Ground_1.Destroy();

	if (WindowManager) {
		WindowManager->Destroy();

		delete WindowManager;
		WindowManager = nullptr;
	}


	if (Camera) {
		delete Camera;
		Camera = nullptr;
	}
}
#include <iostream>
#include "Source.h"
#include "Ground.h"
#include "Wall.h"
#include "Texture.h"

Ground Ground_1(300);

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

	Ground_1.Initialize(Ground_1.vertices, 300, "Shader.VertText", "Shader.FragText");

	// Create the projection matrix for our camera and make the near field closer and the far field farther
	Camera->SetPersepective(radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	Camera->PositionCamera(0, 0, 6, 0, 0);

	Ground_1.SetCamera(Camera);
	Ground_1.SetPosition(vec3(0, 0, 0));
}



void Source::GameLoop() {

	while (WindowManager->ProcessInput(true)) {
		TimeManager::Instance().CalculateFrameRate(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Ground_1.Render();

		//TimeManager::Instance().Sleep(1);

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
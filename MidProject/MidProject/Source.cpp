#include <iostream>
#include "Source.h"
#include "Ground.h"

GraphicsObject Floor, G;
Ground Ground_1();

Vertex3 Triangle[4] = { Vertex3(vec3(-10.0,-2.0, 0.0),  vec4(0, 0, 0, 1)),
						Vertex3(vec3(-10.0,-2.0, 10.0), vec4(0, 0, 0, 1)),
						Vertex3(vec3( 0.0, -2.0, 10.0), vec4(0, 0, 0, 1)),
						Vertex3(vec3( 0.0, -2.0, 0.0),  vec4(0, 0, 0, 1)),
};

int Index = 0;

int Source::Main() {

	Initialize();

	GameLoop();

	Destroy();

	return 0;
}
/*
void quad(int a, int b, int c, int d)
{
	for (int i = 0; i < 100; i += 10) {
		for (int j = 0; j < 100; j += 10) {
			// Triangle 1
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[a].xyz + vec3(j, 0, i); Index++;
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[b].xyz + vec3(j, 0, i); Index++;
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[c].xyz + vec3(j, 0, i); Index++;
	
			// Triangle 2
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[a].xyz + vec3(j, 0, i); Index++;
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[c].xyz + vec3(j, 0, i); Index++;
			Ground[Index].rgba = vec4(1, 1, 1, 1); Ground[Index].xyz = Triangle[d].xyz + vec3(j, 0, i); Index++;
		}
	}
}
*/
void Source::Initialize() {

	if (!WindowManager || WindowManager->Initialize(ScreenWidth, ScreenHeight, "MidTerm Project", false) != 0) {

		exit(-1);
	}

	// Tell OpenGl we want a 3D viewport the same size as the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Tells OpenGl we want depth testing so it renders the order correctly
	glEnable(GL_DEPTH_TEST);

	//quad(0, 1, 2, 3);
	
	//G.Initialize(Ground, 1200, "Shader.Vert", "Shader.Frag");

	Ground_1.Init();

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
		//G.Render();
		//Floor.Render();
		TimeManager::Instance().Sleep(10);

		WindowManager->SwapTheBuffers();
	}
}


void Source::Destroy() {

	Floor.Destroy();

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
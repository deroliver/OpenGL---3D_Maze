#include "InputManager.h"
#include "TimeManager.h"


void InputManager::KeyPressed(InputCode c) {

	if (Camera == nullptr)
		return;


	switch (c) {
	
	case Up: 
		Camera->MoveCamera(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;

	case Down:
		Camera->MoveCamera(-1 * Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;

	case Left:
		Camera->Strafe(-1 * Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;

	case Right:
		Camera->Strafe(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;
	}
}



void InputManager::MouseMoved(float X, float Y) {

	if (Camera == nullptr)
		return;

	Camera->SetViewByMouse(X, Y);
}
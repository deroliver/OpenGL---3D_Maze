#include "InputManager.h"
#include "TimeManager.h"

// Takes a code - Depending on the value, moves the camera
void InputManager::KeyPressed(InputCode c) {

	// If there is no camera, return
	if (Camera == nullptr)
		return;

	// Depending on the code, move the camera back or forward fixed by a speed and time slice
	// to make sure the movement is the same on any computer
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


// This sends in an updated mouse x and y position that should be a delta from (0, 0)
void InputManager::MouseMoved(float X, float Y) {

	// Return if we don't have a valid camera assigned
	if (Camera == nullptr)
		return;

	// Have our manager send the mouse x and y deltas to our camera to process the rotations
	Camera->SetViewByMouse(X, Y);
}
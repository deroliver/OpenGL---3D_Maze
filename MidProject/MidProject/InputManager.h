#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define GLM_FORCE_RADIANS	

#include "Camera.h"

enum InputCode {

	Escape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,

};


class InputManager {

public:

	// Takes a code and sends it to the camera 
	void KeyPressed(InputCode);

	// Set and get the current camera
	void SetCamera(Camera *Cam) { Camera = Cam; }
	Camera *GetCamera() { return Camera; }

	// Sends an updated mouse x and y position
	void MouseMoved(float X, float Y);

protected:

	// Pointer to Camer object
	Camera *Camera;
};

#endif
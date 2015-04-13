#ifndef CAMERA_H_
#define CAMERA_H_

#define PI 3.14159265358979323846264338327950288	// Define PI
#define GLM_FORCE_RADIANS							// Force GLM to use radians


#include <fstream>
#include <glm\glm.hpp>						// Using the GLM math library
#include <glm/gtc/matrix_transform.hpp>					
#include <glm/gtx/transform2.hpp>
using namespace glm;

// Camera class to manage movement
class Camera {

public:
	Camera();

	// Sets and returns a persective matrix built from the field of view, aspect, and near/far planes
	glm::mat4 SetPersepective(float fov, float aspect, float near, float far);

	// Builds and returns a rotation matrix from the yaw and pitch rotations
	glm::mat4 GetRotationMat();

	// Returns Projection Matrix
	glm::mat4 GetProjMat() { return Proj_Mat; }

	// Returns the current view matrix according to the camera's position and rotation
	glm::mat4 GetViewMat();

	// Sets and gets the camera's position
	void SetPosition(glm::vec3 pos) { Position = pos; }
	glm::vec3 GetPosition() { return Position; }

	// Calculates the current view from position and rotation matrix
	glm::vec3 GetView();

	// Returns camera's up vector
	glm::vec3 GetUp();

	// Returns the camera's right vector - Perpendicular to the view and up vectors
	glm::vec3 GetRight();



	// Sets and gets Yaw
	float GetYaw() { return Yaw; }
	void SetYaw(float yaw)	{ Yaw = yaw; }
	
	// Sets and gets Pitch
	float GetPitch() { return Pitch; }
	void SetPitch(float pitch) { Pitch = pitch; }

	// Sets and gets camera's movment Speed
	float GetSpeed() { return Speed; }
	void SetSpeed(float speed) { Speed = speed; }

	// Sets and gets camera's rotation Speed
	float GetRotationSpeed() { return RotationSpeed; }
	void SetRotationSpeed(float rotSpeed) { RotationSpeed = rotSpeed; }

	// Sets the pitch and yaw of camera from the mouse x and mouse y
	void SetViewByMouse(float X, float Y);

	// Sets the position and the yaw and pitch rodations
	void PositionCamera(float posX, float posY, float posZ, float yaw, float pitch);

	// This will move the camera forward or backward depending on speed
	void MoveCamera(float speed);

	// Strafes the camera left or right depending on speed
	void Strafe(float speed);

protected:
	glm::mat4 Proj_Mat;				// Camera's projection matrix

	glm::vec3 Position;				// Camera's position	

	float Speed = 10.0;				// Camera's Speed
	float RotationSpeed = 2.0;		// Camera's rotation speed
	float Yaw = 0.0;				// The horizantal rotation angle - Y-Axis
	float Pitch = 0.0;				// The vertical rotation angle - X-Axis

	double MouseSpeed = 0.001;		// Speed for the mouse rotations



};

#endif
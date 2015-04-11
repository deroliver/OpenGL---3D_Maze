#ifndef CAMERA_H_
#define CAMERA_H_

#define PI 3.14159265358979323846264338327950288
#define GLM_FORCE_RADIANS	


#include <fstream>
#include <glm\glm.hpp>	
#include <glm/gtc/matrix_transform.hpp>					
#include <glm/gtx/transform2.hpp>
using namespace glm;


class Camera {

public:
	Camera();

	// Sets and returns a persective matrix built from the field of view, aspect, and near/far planes
	mat4 SetPersepective(float fov, float aspect, float near, float far);

	// Builds and returns a rotation matrix from the yaw and pitch rotations
	mat4 GetRotationMat();

	// Returns Projection Matrix
	mat4 GetProjMat() { return Proj_Mat; }

	// Returns the current view matrix according to the camera's position and rotation
	mat4 GetViewMat();

	// Sets and gets the camera's position
	void SetPosition(vec3 pos) { Position = pos; }
	vec3 GetPosition() { return Position;  }

	// Calculates the current view from position and rotation matrix
	vec3 GetView();

	// Returns camera's up vector
	vec3 GetUp();

	// Returns the camera's right vector - Perpendicular to the view and up vectors
	vec3 GetRight();



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
	mat4 Proj_Mat;

	vec3 Position;

	float Speed = 5.0;
	float RotationSpeed = 2.0;
	float Yaw = 0.0;
	float Pitch = 0.0;

	double MouseSpeed = 0.001;



};

#endif
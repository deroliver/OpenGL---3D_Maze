#include "Camera.h"

// Default Constructor - Sets the cameras position to the origin
Camera::Camera() {

	Position = vec3(0.0, 0.0, 0.0);
}


// Sets and returns camera's perspective matrix
mat4 Camera::SetPersepective(float fov, float aspect, float near, float far) {

	// Creates projection matrix
	Proj_Mat = perspective(fov, aspect, near, far);

	return Proj_Mat;
}


// Sets the camera's position and rotation values
void Camera::PositionCamera(float posX, float posY, float posZ, float yaw, float pitch) {

	Position = vec3(posX, posY, posZ);
	Yaw = yaw;
	Pitch = pitch;
}


// Builds and returns a rotation matrix from yaw and pitch rotations
glm::mat4 Camera::GetRotationMat() {
	
	// Creates identity matrix 
	mat4 rotationMat(1.0f);

	// Add the pitch rotation along the x-axis
	rotationMat = rotate(rotationMat, Pitch, vec3(1, 0, 0));
	
	// Add the yaw rotation along the y-axis
	rotationMat = rotate(rotationMat, Yaw, vec3(0, 1, 0));

	// Return final rotation matrix
	return rotationMat;
}


// Returns camera's view matrix
mat4 Camera::GetViewMat() {

	// Return a view matrix by multiplying our rotation by the inverse or a translation matrix
	return GetRotationMat() * inverse(translate(mat4(), Position));
}


// Returns current view vector - Direction camera is looking
vec3 Camera::GetView() {

	//Calculate view vector by taking

	vec4 viewVector = inverse(GetRotationMat()) * vec4(0, 0, -1, 1);

	return vec3(viewVector);
}


vec3 Camera::GetRight() {

	vec4 rightVector = inverse(GetRotationMat()) * vec4(1, 0, 0, 1);

	return vec3(rightVector);
}


void Camera::MoveCamera(float speed) {
	
	vec3 viewVector = GetView();

	Position.x += viewVector.x * speed;
	Position.z += viewVector.z * speed;
}


void Camera::Strafe(float speed) {

	vec3 rightVector = GetRight();

	Position.x += rightVector.x * speed;
	Position.z += rightVector.z * speed;
}


void Camera::SetViewByMouse(float X, float Y) {
	
	Yaw += X * MouseSpeed;

	Pitch += Y * MouseSpeed;

	if (Yaw > 2 * PI)
		Yaw = 0;

	if (Yaw < 0)
		Yaw = 2 * PI;

	if (Pitch > radians(75.0f))
		Pitch = radians(75.0f);

	if (Pitch < radians(-75.0f))
		Pitch = radians(-75.0f);
}



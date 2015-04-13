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

	// Calculate the up vector by taking the inverse of the rotation matrix multiplied by a vector looking down the negative z-axis
	vec4 viewVector = inverse(GetRotationMat()) * vec4(0, 0, -1, 1);

	// Cast the vec4 to a vec3
	return vec3(viewVector);
}


vec3 Camera::GetRight() {

	// Calculate the right vector by taking the inverse of the rotation matrix multiplied by a default right vector
	vec4 rightVector = inverse(GetRotationMat()) * vec4(1, 0, 0, 1);

	// Cast the vec4 to a vec3
	return vec3(rightVector);
}

vec3 Camera::GetUp() {

	// Calculate the up vector by taking the inverse of the rotation matrix multiplied by a default up vector
	vec4 UpVector = inverse(GetRotationMat()) * vec4(0, 1, 0, 1);

	// Cast the vec4 to a vec3
	return vec3(UpVector);
}


void Camera::MoveCamera(float speed) {
	
	// Get normalized view vector - Direction we are looking
	vec3 viewVector = GetView();

	// Move our camera forward or backward in the direction of the view vector(where you are looking)
	Position.x += viewVector.x * speed;
	Position.z += viewVector.z * speed;


	// If statements to keep the Camera inside the SkyBox
	if (Position.x > 108.0) 
		Position.x = 108.0;

	if (Position.x < -78.0) 
		Position.x = -78.0;

	if (Position.z > 118.0)
		Position.z = 118.0;

	if (Position.z < -68.0)
		Position.z = -68.0;
}


void Camera::Strafe(float speed) {

	// Get the normalizes right vector - Perpendicular to our view
	vec3 rightVector = GetRight();

	// Move camera right or left in direction of the right vector
	Position.x += rightVector.x * speed;						// Add acceleration to position's X
	Position.z += rightVector.z * speed;						// Add acceleration to position's Z


	// If statements to keep the Camera inside the SkyBox
	if (Position.x > 108.0)
		Position.x = 108.0;

	if (Position.x < -78.0)
		Position.x = -78.0;

	if (Position.z > 118.0)
		Position.z = 118.0;

	if (Position.z < -68.0)
		Position.z = -68.0;
}


void Camera::SetViewByMouse(float X, float Y) {
	
	// Rotate the pitch by the mouse's x offset, multiplied by the mouse rotationspeed variable
	Yaw += X * MouseSpeed;

	// Rotate the pitch by the mouse's y offset, multiplied by the mouse rotationspeed variable
	Pitch += Y * MouseSpeed;

	// Yaw is capped between 0 and 360
	if (Yaw > 2 * PI)
		Yaw = 0;
	if (Yaw < 0)
		Yaw = 2 * PI;

	// Pitch is capped to 75 degrees up and -75 degrees down
	if (Pitch > radians(75.0f))
		Pitch = radians(75.0f);
	if (Pitch < radians(-75.0f))
		Pitch = radians(-75.0f);
}



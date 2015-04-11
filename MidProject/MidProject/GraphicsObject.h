#ifndef GRAPHICSOBJECT_H_
#define GRAPHICSOBJECT_H_

#define GLEW_STATIC
#define GLM_FORCE_RADIANS	

#include <stdio.h>
#include <stdlib.h>
#include "GL\glew.h"
#include "glm\glm.hpp"									// Used for the GLM math library
#include <glm/gtc/matrix_transform.hpp>					// Used for the GLM math library
#include <glm/gtx/transform2.hpp>						// Used for the GLM math library
#include "ShaderManager.h"
#include "Camera.h"
#include "Texture.h"

using namespace glm;

//static int texture_num = GL_TEXTURE1;

// Used to store attributes for a vertex
class Vertex3 {

public:
	Vertex3() {}
	Vertex3(vec3 v1, vec4 v2) : xyz(v1), rgba(v2) {}
	vec3 xyz;
	vec4 rgba;
	vec2 tex;
};

// Handles initializing, rendering, and destroying a 3D object
class GraphicsObject {

public:

	// Used for handling index properties for vertex properties
	static const GLuint VertexIndex = 0;		// For the x,y,z, vertices
	static const GLuint ColorIndex = 1;			// For the r,g,b,a colors
	static const GLuint TextureIndex = 2;		// For the u,v texture coordinates
	static const GLuint NormalIndex = 3;		// For the x,y,z normals

	// Scale of model is set to 100% by default
	GraphicsObject() { Scale = vec3(1.0f, 1.0f, 1.0f); }
	~GraphicsObject() { Destroy(); }

	// Uses the data passed to initialize VBO and VAO, and location of the vertex/fragment shaders
	void Initialize(Vertex3 Vertices[], int vLength, std::string VertexShader, std::string FragmentShader);

	// Draws the Object
	void Render();

	// Setter + Getter function for position
	vec3 GetPosition() { return Position; }
	void SetPosition(vec3 pos) { Position = pos; }

	// Setter + Getter function for rotation
	vec3 GetRotation() { return Rotation; }
	void SetRotation(vec3 rot) { Rotation = rot; }

	// Setter + Getter function for scale
	vec3 GetScale() { return Scale; }
	void SetScale(vec3 scal) { Scale = scal; }

	// Setter + Getter function for the camera
	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *cam) { Camera = cam; }

	// Cleans up
	void Destroy();

protected:

	Vertex3 *Vertices;					// The list of vertices for this object

	GLint VerticesLength;				// The length of the list of vertices

	GLuint VertexBufferID;				// The VBO ID stored by the VAO
	GLuint VertexArrayObjectID;			// The VAO ID to bind		

	GLuint TexBufferID;
	GLuint texID;

	vec3 Position;						// Object's position
	vec3 Rotation;						// Object's rotation
	vec3 Scale;							// Object's scale
		
	ShaderManager Shader;						// Shader object to initialize + run shaders

	Camera *Camera;						// Add camera in order to access matrices
};


#endif
#ifndef SKYBOX_H_
#define SKYBOX_H_
#include "GraphicsObject.h"

// The vertices for the skybox
const vec3 Skybox_Vertices[8] = {
				vec3( -80.0, -100.0, 120.0),
				vec3( 110.0, -100.0, 120.0),
				vec3( 110.0,  100.0, 120.0),
				vec3( -80.0,  100.0, 120.0),
				vec3( -80.0, -100.0, -70.0),
				vec3( 110.0, -100.0, -70.0),
				vec3( 110.0,  100.0, -70.0),
				vec3( -80.0,  100.0, -70.0),
};


// Skybox class - Extends the GraphicsObject class
class SkyBox : public GraphicsObject {
public:
	// Holds information about the vertices
	Vertex3 vertices[36];
	int Index = 0;

	// Constructor - sets the VerticesLength
	SkyBox(int length);

	// Adds Vertices to the array
	void Triangle(unsigned int A, unsigned int B, unsigned int C);

	// Creates a quad using two triangles
	void Quad(unsigned int A, unsigned int B, unsigned int C, unsigned int D);

	// Draws the SkyBox
	void Render();

	// Initializes the SkyBox and the shaders
	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag);
};

#endif
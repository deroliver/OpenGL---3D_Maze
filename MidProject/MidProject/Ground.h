#ifndef GROUND_H_
#define GROUND_H_
#include "GraphicsObject.h"

const Vertex3 Quad[4] = { Vertex3(vec3(-10.0, -5.0,  0.0), vec4(0 , 0, 0, 1)),
						  Vertex3(vec3(-10.0, -5.0, 10.0), vec4(0, 0, 0, 1)),
						  Vertex3(vec3( 0.0,  -5.0, 10.0), vec4(0, 0, 0, 1)),
						  Vertex3(vec3( 0.0,  -5.0,  0.0), vec4(0, 0, 0, 1)),
};


// Class that extends the GraphicsObject class - Draws the textured ground
class Ground : public GraphicsObject {
public:
	// Holds vertex information for the vertices
	Vertex3 vertices[2166];
	int Index = 0;

	// Constructor, sets the VerticesLength
	Ground(int length);

	// Draws the ground
	void Render();

	// Initializes the ground and the shaders
	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag);
};

#endif


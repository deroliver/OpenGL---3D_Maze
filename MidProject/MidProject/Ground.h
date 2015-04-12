#ifndef GROUND_H_
#define GROUND_H_

#include "GraphicsObject.h"

const Vertex3 Quad[4] = { Vertex3(vec3(-10.0, -5.0,  0.0), vec4(0 , 0, 0, 1)),
						  Vertex3(vec3(-10.0, -5.0, 10.0), vec4(0, 0, 0, 1)),
						  Vertex3(vec3( 0.0,  -5.0, 10.0), vec4(0, 0, 0, 1)),
						  Vertex3(vec3( 0.0,  -5.0,  0.0), vec4(0, 0, 0, 1)),
};


class Ground : public GraphicsObject {
public:
	Vertex3 vertices[486];
	int Index = 0;

	Ground(int length);

	void Render();

	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag);
};

#endif


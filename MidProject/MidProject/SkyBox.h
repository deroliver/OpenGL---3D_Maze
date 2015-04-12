#ifndef SKYBOX_H_
#define SKYBOX_H_
#include "GraphicsObject.h"

const vec3 Skybox_Vertices[8] = {
				vec3(-100.0, -100.0,  100.0),
				vec3( 100.0, -100.0,  100.0),
				vec3( 100.0,  100.0,  100.0),
				vec3(-100.0,  100.0,  100.0),
				vec3(-100.0, -100.0, -100.0),
				vec3( 100.0, -100.0, -100.0),
				vec3( 100.0,  100.0, -100.0),
				vec3(-100.0,  100.0, -100.0),
};


class SkyBox : public GraphicsObject {
public:

	Vertex3 vertices[200];
	int Index = 0;

	SkyBox(int length);

	void Triangle(unsigned int A, unsigned int B, unsigned int C);

	void Quad(unsigned int A, unsigned int B, unsigned int C, unsigned int D);


	void Render();


	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag);
};

#endif
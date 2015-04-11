#ifndef MAZEBLOCK_H_
#define MAZEBLOCK_H_

#include "GraphicsObject.h"

const Vertex3 Quad[8] = {
	// Front Face
	Vertex3(vec3(-10.0, -2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  3.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0, -2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0, -2.0, 0.0), vec4(0, 0, 0, 1)),

	// Rear Face
	Vertex3(vec3(-10.0, -2.0, 5.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  3.0, 5.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0,  3.0, 5.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0, -2.0, 5.0), vec4(0, 0, 0, 1))
};


class MazeBlock : public GraphicsObject {

public:



};


#endif
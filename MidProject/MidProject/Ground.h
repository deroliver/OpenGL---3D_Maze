#ifndef GROUND_H_
#define GROUND_H_

#include "GraphicsObject.h"

class Ground : public GraphicsObject {
private:
	Vertex3 Quad[4];
	Vertex3 vertices[1200];


public:
	Ground() : GraphicsObject() {
		Quad[0] = Vertex3(vec3(-10.0, -2.0,  0.0), vec4(0, 0, 0, 1));
		Quad[1] = Vertex3(vec3(-10.0, -2.0, 10.0), vec4(0, 0, 0, 1));
		Quad[2] = Vertex3(vec3(  0.0, -2.0, 10.0), vec4(0, 0, 0, 1));
		Quad[3] = Vertex3(vec3(  0.0, -2.0,  0.0), vec4(0, 0, 0, 1));

		Init_Vertices();
	}

	void Init_Vertices() {
		int Index = 0;
		for (int i = 0; i < 100; i += 10) {
			for (int j = 0; j < 100; j += 10) {
				// Triangle 1
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[1].xyz + vec3(j, 0, i); Index++;
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[2].xyz + vec3(j, 0, i); Index++;
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[3].xyz + vec3(j, 0, i); Index++;

				// Triangle 2
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[1].xyz + vec3(j, 0, i); Index++;
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[3].xyz + vec3(j, 0, i); Index++;
				vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Quad[4].xyz + vec3(j, 0, i); Index++;
			}
		}
	}

	void Init() {
		Initialize(vertices, 1200, "Shader.Vert", "Shader.Frag");
	}
};

#endif


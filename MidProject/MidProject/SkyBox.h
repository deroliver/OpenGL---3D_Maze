#ifndef SKYBOX_H_
#define SKYBOX_H_
#include "GraphicsObject.h"


Vertex3  Skybox_Vertices[8] = {
				Vertex3(vec3(-40.0, -40.0,  0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3( 40.0, -40.0,  0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3( 40.0,  40.0,  0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3(-40.0,  40.0,  0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3(-40.0, -40.0, -0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3( 40.0, -40.0, -0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3( 40.0,  40.0, -0.5), vec4(1, 1, 1, 1)),
				Vertex3(vec3(-40.0,  40.0, -0.5), vec4(1, 1, 1, 1))
};


class SkyBox : public GraphicsObject {
public:

	Vertex3 vertices[36];
	Vertex3  normals[36];
	int Index = 0;

	SkyBox(int length) : GraphicsObject() {
		VerticesLength = length;
		Quad(1, 5, 6, 2);
		Quad(4, 0, 3, 7);
		Quad(3, 2, 6, 7);
		Quad(4, 5, 1, 0);
		Quad(0, 1, 2, 3);
		Quad(5, 4, 7, 6);
	}

	void Triangle(unsigned int A, unsigned int B, unsigned int C) {

		normals[Index].xyz = normalize(Skybox_Vertices[A].xyz); vertices[Index] = Skybox_Vertices[A]; Index++;

		normals[Index].xyz = normalize(Skybox_Vertices[B].xyz); vertices[Index] = Skybox_Vertices[B]; Index++;

		normals[Index].xyz = normalize(Skybox_Vertices[C].xyz); vertices[Index] = Skybox_Vertices[C]; Index++;
	}

	void Quad(unsigned int A, unsigned int B, unsigned int C, unsigned int D) {

		Triangle(A, B, C);
		Triangle(A, C, D);
	}


	void Render() {

		Shader.TurnOn();

		
		mat4 Proj_Mat = Camera->GetProjMat();
		mat4 View_Mat = Camera->GetViewMat();

		// Create Model Matric at current position
		mat4 Mode_Mat = translate(mat4(1.0f), Position);

		Mode_Mat = scale(Mode_Mat, Scale);

		Mode_Mat = rotate(Mode_Mat, Rotation.x, vec3(1, 0, 0));
		Mode_Mat = rotate(Mode_Mat, Rotation.y, vec3(0, 1, 0));
		Mode_Mat = rotate(Mode_Mat, Rotation.z, vec3(0, 0, 1));

		GLint Mode_MatID = Shader.GetVariable("Mode_Mat");
		GLint View_MatID = Shader.GetVariable("View_Mat");
		GLint Proj_MatID = Shader.GetVariable("Proj_Mat");

		Shader.SetMatrix4(Mode_MatID, 1, false, &Mode_Mat[0][0]);
		Shader.SetMatrix4(View_MatID, 1, false, &View_Mat[0][0]);
		Shader.SetMatrix4(Proj_MatID, 1, false, &Proj_Mat[0][0]);

		// Which VAO is going to be used
		glBindVertexArray(VertexArrayObjectID);

		// Enable vertex information
		glEnableVertexAttribArray(VertexIndex);

		// Enable color information
		glEnableVertexAttribArray(ColorIndex);


		glEnableVertexAttribArray(TextureIndex);

		// Draw triangles from VBO
		glDrawArrays(GL_TRIANGLES, 0, VerticesLength);

		// Disable color index
		glDisableVertexAttribArray(ColorIndex);

		// Disable vertex index
		glDisableVertexAttribArray(VertexIndex);

		// Reset current VAO to 0
		glBindVertexArray(0);

		// Other objects won't be using the same shader
		Shader.TurnOff();
	}


	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag) {

		Shader.Initialize(Vertex, Frag);

		glGenTextures(1, &TexBufferID);
		glActiveTexture(This_Texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, TexBufferID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		int TexRight = MyLoadCubeMapBitmap("skybox\\ww_r.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		int TexLeft = MyLoadCubeMapBitmap("skybox\\ww_l.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		int TexTop = MyLoadCubeMapBitmap("skybox\\ww_u.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		int TexBottom = MyLoadCubeMapBitmap("skybox\\ww_d.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		int TexFront = MyLoadCubeMapBitmap("skybox\\ww_f.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		int TexBack = MyLoadCubeMapBitmap("skybox\\ww_b.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

		texID = Shader.GetVariable("texMap");
		Shader.SetInt(texID, TexBufferID);

		

		glEnable(GL_TEXTURE_CUBE_MAP);

		// Store the vertices and length in member variables
		Vertices = vertices;
		VerticesLength = length;

		// Reset the errors
		GLenum ErrorCheckValue = glGetError();

		// Create the Vertex Array Object
		glGenVertexArrays(1, &VertexArrayObjectID);
		glBindVertexArray(VertexArrayObjectID);

		// Create the Vertex Buffer Object
		glGenBuffers(1, &VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

		// Store vertices in the VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * length, Vertices, GL_STATIC_DRAW);

		// Tell OpenGL what the format of each vertex is within the buffer
		glVertexAttribPointer(VertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), 0);

		// Add color attributes to VAO and VBO
		glVertexAttribPointer(ColorIndex, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)sizeof(Vertices[0].xyz));

		glVertexAttribPointer(TextureIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)(sizeof(Vertices[0].xyz) + sizeof(Vertices[0].rgba)));

		// Check for errors
		ErrorCheckValue = glGetError();

		if (ErrorCheckValue != GL_NO_ERROR) {
			fprintf(stderr, "Error: Could not create VBO and VAO, Error ID: %d\n", ErrorCheckValue);
			exit(-1);
		}
	}

};


#endif
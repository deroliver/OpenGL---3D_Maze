#ifndef WALL_H_
#define WALL_H_

#include "GraphicsObject.h"

const Vertex3 WallBlock1[8] = {
	// Front Face
	Vertex3(vec3(-10.0,  -5.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(-10.0,  20.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3( 80.0,  20.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3( 80.0,  -5.0, 0.0), vec4(1, 1, 1, 1)),

	// Rear Face
	Vertex3(vec3(-10.0,  -5.0, 1.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(-10.0,  20.0, 1.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3( 80.0,  20.0, 1.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3( 80.0,  -5.0, 1.0), vec4(1, 1, 1, 1))
};


const Vertex3 WallBlock2[8] = {
	// Front Face
	Vertex3(vec3(-10.0, -5.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(-10.0, 20.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(  1.0, 20.0, 0.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(  1.0, -5.0, 0.0), vec4(1, 1, 1, 1)),

	// Rear Face
	Vertex3(vec3(-10.0, -5.0, 80.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(-10.0, 20.0, 80.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(1.0,  20.0, 80.0), vec4(1, 1, 1, 1)),
	Vertex3(vec3(1.0, -5.0, 80.0), vec4(1, 1, 1, 1))
};


class Wall : public GraphicsObject {
public:
	Vertex3 vertices[36];
	int Index = 0;

	Wall(int length, bool D) {
		VerticesLength = length;
		if (D = true) {
			Face1(1, 0, 3, 2, 0, 0);
			Face1(2, 3, 7, 6, 0, 0);
			Face1(3, 0, 4, 7, 0, 0);
			Face1(6, 5, 1, 2, 0, 0);
			Face1(4, 5, 6, 7, 0, 0);
			Face1(5, 4, 0, 1, 0, 0);
		}
		else {
			Face2(1, 0, 3, 2, 0, 0);
			Face2(2, 3, 7, 6, 0, 0);
			Face2(3, 0, 4, 7, 0, 0);
			Face2(6, 5, 1, 2, 0, 0);
			Face2(4, 5, 6, 7, 0, 0);
			Face2(5, 4, 0, 1, 0, 0);
		}

	}

	void Face1(int a, int b, int c, int d, int xOff, int yOff)  {
		// First triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[b].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[c].xyz + vec3(xOff, 0, yOff); Index++;

		// Second triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[c].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock1[d].xyz + vec3(xOff, 0, yOff); Index++;
	}


	void Face2(int a, int b, int c, int d, int xOff, int yOff)  {
		// First triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[b].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[c].xyz + vec3(xOff, 0, yOff); Index++;

		// Second triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[c].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = WallBlock2[d].xyz + vec3(xOff, 0, yOff); Index++;
	}

	void Render() {

		Shader.TurnOn();

		//glGenTextures(1, &TexBufferID);
		//glBindTexture(GL_TEXTURE_2D, TexBufferID);

		//GLint IDT = MyLoadBitmap("Brick.bmp", GL_TEXTURE_2D, true);
		//texID = Shader.GetVariable("texMap");
		//Shader.SetInt(texID, 0);

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


		//glEnableVertexAttribArray(TextureIndex);

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

		//glVertexAttribPointer(TextureIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)(sizeof(Vertices[0].xyz) + sizeof(Vertices[0].rgba)));

		// Check for errors
		ErrorCheckValue = glGetError();

		if (ErrorCheckValue != GL_NO_ERROR) {
			fprintf(stderr, "Error: Could not create VBO and VAO, Error ID: %d\n", ErrorCheckValue);
			exit(-1);
		}
	}
};





#endif
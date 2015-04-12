#ifndef MAZEBLOCK_H_
#define MAZEBLOCK_H_

#include "GraphicsObject.h"
#include <random>
#include <stack>

std::random_device rd;
std::mt19937 Gen(rd());
std::uniform_int_distribution<> Random(1, 4);

const Vertex3 Block[8] = {
	// Front Face
	Vertex3(vec3(-10.0, -5.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0,  2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0, -5.0, 0.0), vec4(0, 0, 0, 1)),

	// Rear Face
	Vertex3(vec3(-10.0, -5.0, 0.25), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  2.0, 0.25), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0,  2.0, 0.25), vec4(0, 0, 0, 1)),
	Vertex3(vec3( -5.0, -5.0, 0.25), vec4(0, 0, 0, 1))
};

const Vertex3 Block2[8] = {
	// Front Face
	Vertex3(vec3(-9.75, -5.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-9.75,  2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-9.75,  2.0, 5.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-9.75, -5.0, 5.0), vec4(0, 0, 0, 1)),

	// Rear Face
	Vertex3(vec3(-10.0, -5.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  2.0, 0.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0,  2.0, 5.0), vec4(0, 0, 0, 1)),
	Vertex3(vec3(-10.0, -5.0, 5.0), vec4(0, 0, 0, 1))
};

// Class to keep track of Rooms that have been visited, as well as drawing of the walls
class MazeSpace {
public:
	bool DrawX = true;
	bool DrawY = true;
	bool Visited = false;
};

// Class to keep track of the positions in the maze
class XY {
public:
	int X;
	int Y;
};


class MazeBlocks : public GraphicsObject {

public:
	// The array to keep track of the Walls
	MazeSpace Maze[11][11];

	// The array to keep track of the rooms that have been visited
	MazeSpace MazeRoom[12][12];
	
	// Vertices for the maze walls
	Vertex3 vertices[16000];

	// Stack to hold the positions for the rooms in the maze
	std::stack<XY> Rooms;


	int Index = 0;

	// Constructor
	MazeBlocks(int length) {
		for (int i = 0; i <= 12; i++) {
			MazeRoom[i][0].Visited = true;
			MazeRoom[0][i].Visited = true;
			MazeRoom[12][i].Visited = true;
			MazeRoom[i][12].Visited = true;

		}
		GenerateMaze(1, 4);
		VerticesLength = length;
		for (int i = 1; i <= 11; i++) {
			for (int j = 1; j <= 12; j++) {
				if (Maze[i][j].DrawY) {
					Face(1, 0, 3, 2, 5 * i, 5 * j);
					Face(2, 3, 7, 6, 5 * i, 5 * j);
					Face(3, 0, 4, 7, 5 * i, 5 * j);
					Face(6, 5, 1, 2, 5 * i, 5 * j);
					Face(4, 5, 6, 7, 5 * i, 5 * j);
					Face(5, 4, 0, 1, 5 * i, 5 * j);
				}
			}
		}
	
		for (int i = 1; i <= 12; i++) {
			for (int j = 1; j <= 11; j++) {
				if (Maze[i][j].DrawX){
					Face2(1, 0, 3, 2, 5 * i, 5 * j);
					Face2(2, 3, 7, 6, 5 * i, 5 * j);
					Face2(3, 0, 4, 7, 5 * i, 5 * j);
					Face2(6, 5, 1, 2, 5 * i, 5 * j);
					Face2(4, 5, 6, 7, 5 * i, 5 * j);
					Face2(5, 4, 0, 1, 5 * i, 5 * j);
				}
			}
		}
	
	}

	
	void GenerateMaze(int x, int y) {
	
		XY room;
		room.X = x;
		room.Y = y;	
		

		MazeRoom[x][y].Visited = true;

		bool all = true;
		for (int i = 0; i <= 11; i++) {
			for (int j = 0; j <= 11; j++) {
				if (!MazeRoom[i][j].Visited)
					all = false;
			}
		}

		if (all)
			return;

		fprintf(stderr, "Value of X: %d\n Value of Y: %d\n", x, y);
		if (MazeRoom[x - 1][y].Visited && MazeRoom[x + 1][y].Visited && MazeRoom[x][y - 1].Visited && MazeRoom[x][y + 1].Visited) {
			Rooms.pop();
			GenerateMaze(Rooms.top().X, Rooms.top().Y);
		}

		Rooms.push(room);

		int nX = x, nY = y;
		bool found = false;
		int R = 0;
		
		while (!found) {
			int R = Random(Gen);
			switch (R) {
			case 1:
				if (!MazeRoom[x - 1][y].Visited){
					Maze[x][y].DrawX = false;
					nX = x - 1; nY = y;
					found = true;
				}				
				break;

			case 2:		
				if (!MazeRoom[x + 1][y].Visited){
					Maze[x + 1][y].DrawX = false;
					nX = x + 1; nY = y;
					found = true;
					}
				break;

			case 3:		
				if (!MazeRoom[x][y - 1].Visited){
					Maze[x][y].DrawY = false;
					nX = x; nY = y - 1;
					found = true;
					}
				break;
			
			case 4:	
				if (!MazeRoom[x][y + 1].Visited){
					Maze[x][y + 1].DrawY = false;
					nX = x; nY = y + 1;
					found = true;
				}			
				break;
			}
			bool all = true;
			for (int i = 0; i <= 11; i++) {
				for (int j = 0; j <= 11; j++) {
					if (!MazeRoom[i][j].Visited)
						all = false;
				}
			}

			if (all)
				return;
		}
		GenerateMaze(nX, nY);
	}
	

	void Face(int a, int b, int c, int d, int xOff, int yOff)  {
		// First triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[b].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[c].xyz + vec3(xOff, 0, yOff); Index++;

		// Second triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[c].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block[d].xyz + vec3(xOff, 0, yOff); Index++;
	}

	void Face2(int a, int b, int c, int d, int xOff, int yOff)  {
		// First triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[b].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[c].xyz + vec3(xOff, 0, yOff); Index++;

		// Second triangle of the face
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[a].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[c].xyz + vec3(xOff, 0, yOff); Index++;
		vertices[Index].rgba = vec4(1, 1, 1, 1); vertices[Index].xyz = Block2[d].xyz + vec3(xOff, 0, yOff); Index++;
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
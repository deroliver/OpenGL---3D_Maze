#include "MazeBlocks.h"

std::random_device rd;
std::mt19937 Gen(rd());
std::uniform_int_distribution<> Random(1, 4);
std::uniform_int_distribution<> EndRand(2, 16);

// Constructor to initialize the maze
MazeBlocks::MazeBlocks(int length) : GraphicsObject() {

	End.X = EndRand(Gen);
	End.Y = EndRand(Gen);

	// Initializes the maze
	InitMaze();

	// Set the VerticesLength
	VerticesLength = length;

	// Draws the walls facing the Vertically
	for (int i = 1; i <= 17; i++) {
		for (int j = 1; j <= 18; j++) {
			// Sets up the end block
			if (i == End.X && j == End.Y) {
				FaceEnd(1, 0, 3, 2, 10 * i, 10 * j);
				FaceEnd(2, 3, 7, 6, 10 * i, 10 * j);
				FaceEnd(3, 0, 4, 7, 10 * i, 10 * j);
				FaceEnd(6, 5, 1, 2, 10 * i, 10 * j);
				FaceEnd(4, 5, 6, 7, 10 * i, 10 * j);
				FaceEnd(5, 4, 0, 1, 10 * i, 10 * j);
			}
			// If DrawY is true at the specified point in the array
			if (Maze[i][j].DrawY) {
				// Create a wall
				Face(1, 0, 3, 2, 10 * i, 10 * j);
				Face(2, 3, 7, 6, 10 * i, 10 * j);
				Face(3, 0, 4, 7, 10 * i, 10 * j);
				Face(6, 5, 1, 2, 10 * i, 10 * j);
				Face(4, 5, 6, 7, 10 * i, 10 * j);
				Face(5, 4, 0, 1, 10 * i, 10 * j);
				CreateRect(10 * i, 10 * j);
			}
		}
	}

	// Draws the walls facing the Vertically
	for (int i = 1; i <= 18; i++) {
		for (int j = 1; j <= 17; j++) {
			// Sets up the end block
			if (i == End.X && j == End.Y) {
				FaceEnd(1, 0, 3, 2, 10 * i, 10 * j);
				FaceEnd(2, 3, 7, 6, 10 * i, 10 * j);
				FaceEnd(3, 0, 4, 7, 10 * i, 10 * j);
				FaceEnd(6, 5, 1, 2, 10 * i, 10 * j);
				FaceEnd(4, 5, 6, 7, 10 * i, 10 * j);
				FaceEnd(5, 4, 0, 1, 10 * i, 10 * j);
			}
			// If DrawX is true at the specified point in the array
			if (Maze[i][j].DrawX){
				// Create a wall
				Face2(1, 0, 3, 2, 10 * i, 10 * j);
				Face2(2, 3, 7, 6, 10 * i, 10 * j);
				Face2(3, 0, 4, 7, 10 * i, 10 * j);
				Face2(6, 5, 1, 2, 10 * i, 10 * j);
				Face2(4, 5, 6, 7, 10 * i, 10 * j);
				Face2(5, 4, 0, 1, 10 * i, 10 * j);
			}
		}
	}
}



void MazeBlocks::Face(int A, int B, int C, int D, int xOff, int zOff) {
	// First triangle of the face
	vertices[Index].norm = normalize(Block[A]); vertices[Index].xyz = Block[A] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[B]); vertices[Index].xyz = Block[B] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[C]); vertices[Index].xyz = Block[C] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 1.0); Index++;

	// Second triangle of the face
	vertices[Index].norm = normalize(Block[A]); vertices[Index].xyz = Block[A] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[B]); vertices[Index].xyz = Block[C] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 1.0); Index++;
	vertices[Index].norm = normalize(Block[C]); vertices[Index].xyz = Block[D] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 1.0); Index++;
}

void MazeBlocks::Face2(int A, int B, int C, int D, int xOff, int zOff) {
	// First triangle of the face
	vertices[Index].norm = normalize(Block[A]); vertices[Index].xyz = Block2[A] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[B]); vertices[Index].xyz = Block2[B] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[C]); vertices[Index].xyz = Block2[C] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 1.0); Index++;

	// Second triangle of the face
	vertices[Index].norm = normalize(Block[A]); vertices[Index].xyz = Block2[A] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 0.0); Index++;
	vertices[Index].norm = normalize(Block[B]); vertices[Index].xyz = Block2[C] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(0.0, 1.0); Index++;
	vertices[Index].norm = normalize(Block[C]); vertices[Index].xyz = Block2[D] + vec3(xOff, 0, zOff); vertices[Index].tex = vec2(1.0, 1.0); Index++;
}

// Creates a rectangle object for each rectangle along the wall
void MazeBlocks::CreateRect(int xOff, int zOff) {
	Rec rect;
	rect.X = Block[0].x + xOff + 5.0;
	rect.Z = Block[0].z + zOff - 0.125;
	rect.Y = Block[0].y + 10;

	Rects.push_back(rect);
}


// Sets the outer edge of the Maze array to visited
void MazeBlocks::InitMaze() {
	for (int i = 0; i <= 18; i++) {
		MazeRoom[i][0].Visited = true;
		MazeRoom[0][i].Visited = true;
		MazeRoom[18][i].Visited = true;
		MazeRoom[i][18].Visited = true;

	}
	// Starting point of the maze
	Maze[1][4].DrawX = false;

	// Calls the recursive function
	GenerateMaze(1, 4);
}

// Checks to see if all the rooms in the maze have been visited
bool MazeBlocks::CheckAll() {
	bool all = true;
	for (int i = 0; i <= 17; i++) {
		for (int j = 0; j <= 17; j++) {
			if (!MazeRoom[i][j].Visited)
				all = false;
		}
	}
	return all;
}

// Recursive function to generate maze
void MazeBlocks::GenerateMaze(int x, int y) {
	
	// Add the current (x, y) position to a stack
	XY room;
	room.X = x;
	room.Y = y;

	// Set the current room to visited
	MazeRoom[x][y].Visited = true;

	// If all rooms have been visited - Return
	if (CheckAll())
		return;

	// If all the rooms surrounding you have been visited
	if (MazeRoom[x - 1][y].Visited && MazeRoom[x + 1][y].Visited && MazeRoom[x][y - 1].Visited && MazeRoom[x][y + 1].Visited) {
		// Move to your previous room
		Rooms.pop();
		GenerateMaze(Rooms.top().X, Rooms.top().Y);
	}
	
	// Add the (x, y) position to the stack
	Rooms.push(room);

	int nX = x, nY = y;
	bool found = false;
	int R = 0;

	// While you haven't found a room to go to 
	while (!found) {

		// Random number 1 - 4
		int R = Random(Gen); 
		switch (R) {
		case 1:
			// If you haven't visited the room to the left
			if (!MazeRoom[x - 1][y].Visited){
				// Set the wall between you and the room to not draw
				Maze[x][y].DrawX = false;
				nX = x - 1; nY = y;
				found = true;
			}
			break;

		case 2:
			// If you haven't visited the room to the right
			if (!MazeRoom[x + 1][y].Visited){
				// Set the wall between you and the room to not draw
				Maze[x + 1][y].DrawX = false;
				nX = x + 1; nY = y;
				found = true;
			}
			break;

		case 3:
			// If you haven't visited the room ahead of you
			if (!MazeRoom[x][y - 1].Visited){
				// Set the wall between you and the room to not draw
				Maze[x][y].DrawY = false;
				nX = x; nY = y - 1;
				found = true;
			}
			break;

		case 4:
			// If you haven't visited the room to the below you
			if (!MazeRoom[x][y + 1].Visited){
				// Set the wall between you and the room to not draw
				Maze[x][y + 1].DrawY = false;
				nX = x; nY = y + 1;
				found = true;
			}
			break;
		}
		// If all rooms have been visited - Return
		if (CheckAll()) {
			return;			
		}

		// Recursively call function using new (x, y) position
		GenerateMaze(nX, nY);
	}
}




void MazeBlocks::FaceEnd(int A, int B, int C, int D, int xOff, int zOff) {

	// First triangle of the face
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[A] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[B] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[C] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;

	// Second triangle of the face
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[A] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[C] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;
	vertices[Index].rgba = vec4(1, 0, 0, 1); vertices[Index].xyz = EndBlock[D] + vec3(xOff + 4.0, 0, zOff + 4.0); Index++;
}




// Function that will render the model to the backbuffer
void MazeBlocks::Render() {

	// Turns on the shader
	Shader.TurnOn();

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(This_Texture);
	glGenTextures(1, &TexBufferID);
	glBindTexture(GL_TEXTURE_2D, TexBufferID);

	texID = Shader.GetVariable("texMap");
	Shader.SetInt(texID, 0);

	// Get the view + projection matrices from the Camera
	mat4 Proj_Mat = Camera->GetProjMat();
	mat4 View_Mat = Camera->GetViewMat();

	// Create Model Matrix at current position
	mat4 Mode_Mat = translate(mat4(1.0f), Position);

	// Create the Model Matrix with the current scale
	Mode_Mat = scale(Mode_Mat, Scale);

	// Add any rotation to the Model Matrix
	Mode_Mat = rotate(Mode_Mat, Rotation.x, vec3(1, 0, 0)); // X-Axis
	Mode_Mat = rotate(Mode_Mat, Rotation.y, vec3(0, 1, 0)); // Y-Axis
	Mode_Mat = rotate(Mode_Mat, Rotation.z, vec3(0, 0, 1)); // Z-Axis

	// Get the variables from the shader for each matrix
	GLint Mode_MatID = Shader.GetVariable("Mode_Mat");
	GLint View_MatID = Shader.GetVariable("View_Mat");
	GLint Proj_MatID = Shader.GetVariable("Proj_Mat");

	// Set the model, view, and projection matrix for the uniform matrices in Vertex shader.
	Shader.SetMatrix4(Mode_MatID, 1, false, &Mode_Mat[0][0]);
	Shader.SetMatrix4(View_MatID, 1, false, &View_Mat[0][0]);
	Shader.SetMatrix4(Proj_MatID, 1, false, &Proj_Mat[0][0]);

	// Tell OpenGL which VAO is going to be used
	glBindVertexArray(VertexArrayObjectID);

	// Enable vertex information within shaders
	glEnableVertexAttribArray(VertexIndex);

	// Enable the texture index
	glEnableVertexAttribArray(TextureIndex);

	// Enable color information within shaders
	glEnableVertexAttribArray(ColorIndex);


	// Draw triangles from VBO
	glDrawArrays(GL_TRIANGLES, 0, VerticesLength);

	// Disable color index
	glDisableVertexAttribArray(ColorIndex);

	// Disable vertex index
	glDisableVertexAttribArray(VertexIndex);

	// Disable texture index
	glDisableVertexAttribArray(TextureIndex);

	// Reset current VAO to 0
	glBindVertexArray(0);

	// Other objects won't be using the same shader
	Shader.TurnOff();
}



// Initialize the model with vertices, length, and the vertex and fragment shader files
void MazeBlocks::Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag) {

	// Create + compile GLSL vertex and fragment shaders
	Shader.Initialize(Vertex, Frag);

	glActiveTexture(This_Texture);

	// Load the bitmap
	int IT = MyLoadBitmap("Wall.bmp", GL_TEXTURE_2D, true);

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

	// Add texture attributes to VAO and VBO
	glVertexAttribPointer(TextureIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)(sizeof(Vertices[0].xyz) + sizeof(Vertices[0].rgba)));


	// Check for errors
	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "Error: Could not create VBO and VAO, Error ID: %d\n", ErrorCheckValue);
		exit(-1);
	}
}
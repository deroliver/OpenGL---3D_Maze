#ifndef MAZEBLOCK_H_
#define MAZEBLOCK_H_

#include "GraphicsObject.h"
#include <stack>
#include <random>

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

// The Vertices for the Horizantal Walls
const vec3 Block[8] = {
	// Front Face
	vec3(-10.0, -5.0, 0.0),
	vec3(-10.0,  8.0, 0.0),
	vec3( -5.0,  8.0, 0.0), 
	vec3( -5.0, -5.0, 0.0), 

	// Rear Face
	vec3(-10.0, -5.0, 0.25),
	vec3(-10.0,  8.0, 0.25), 
	vec3( -5.0,  8.0, 0.25),
	vec3( -5.0, -5.0, 0.25)
};

// The Vertices for the Vertical Walls
const vec3 Block2[8] = {
	// Front Face
	vec3(-9.75, -5.0, 0.0), 
	vec3(-9.75,  8.0, 0.0), 
	vec3(-9.75,  8.0, 5.0), 
	vec3(-9.75, -5.0, 5.0), 

	// Rear Face
	vec3(-10.0, -5.0, 0.0),
	vec3(-10.0,  8.0, 0.0), 
	vec3(-10.0,  8.0, 5.0), 
	vec3(-10.0, -5.0, 5.0), 
};



// Class to create and draw the maze walls
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
	MazeBlocks(int length);

	// Initializes the maze, calls generate maze
	void InitMaze();
	
	// Recursive algorithm to create a maze
	void GenerateMaze(int x, int y);

	// Checks if all the maze rooms have been visited
	bool CheckAll();

	// Creates the Horizantal maze walls
	void Face(int a, int b, int c, int d, int xOff, int yOff);

	// Creates the Vertical maze walls
	void Face2(int a, int b, int c, int d, int xOff, int yOff);

	// Draws the maze walls
	void Render();

	// Initializes the VBO and VAO and location of the vertex/fragment shaders
	void Initialize(Vertex3 vertices[], int length, std::string Vertex, std::string Frag);	
};

#endif
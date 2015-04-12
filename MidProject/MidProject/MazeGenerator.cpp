#include "MazeGenerator.h"

/*

void MazeGenerator::InitMaze() {
	for (int i = 0; i <= 12; i++) {
		MazeRoom[i][0].Visited = true;
		MazeRoom[0][i].Visited = true;
		MazeRoom[12][i].Visited = true;
		MazeRoom[i][12].Visited = true;

	}

	GenerateMaze(1, 4);
}

bool MazeGenerator::CheckAll(){
	bool all = true;
	for (int i = 0; i <= 11; i++) {
		for (int j = 0; j <= 11; j++) {
			if (!MazeRoom[i][j].Visited)
				all = false;
		}
	}
	return all;
}


void MazeGenerator::GenerateMaze(int x, int y) {
	XY room;
	room.X = x;
	room.Y = y;

	MazeRoom[x][y].Visited = true;

	if (CheckAll())
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
		if (CheckAll())
			return;

		GenerateMaze(nX, nY);
	}
	}*/
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/


void SolveMaze(int row, int col, char maze[][100], int rowSz, int colSz, bool& foundEnd, string& finaldir, string currDir) {
    // Base case: Finished already
    if(foundEnd){
        return;
    }
    // Base case: Check bounds
    if(row < 0 || row >= rowSz || col < 0 || col >= colSz){
        return;
    }
    // Base case: breadcrumbs and walls
    if(maze[row][col] == '.' || maze[row][col] == '@'){
        return;
    }
    // Base case: Found finish
    if(maze[row][col] == 'F'){
        foundEnd = true;
        finaldir = currDir;
        return;
    }

    maze[row][col] = '.'; // Put down breadcrumbs

    // General case - Each recursive call must be one step smaller.
    SolveMaze( row - 1, col, maze, rowSz, colSz, foundEnd, finaldir, currDir+"U");   //Up
    SolveMaze( row + 1, col, maze, rowSz, colSz, foundEnd, finaldir, currDir+"D");   //Down
    SolveMaze( row, col - 1, maze, rowSz, colSz, foundEnd, finaldir, currDir+"L");   //Left
    SolveMaze( row, col + 1, maze, rowSz, colSz, foundEnd, finaldir, currDir+"R");   //Right

    if(!foundEnd){
        maze[row][col] = ' '; // If I didn't find the end, pick up the breadcrumb
    }

}

int main()
{
	ifstream mazeFile("maze.txt");
	char maze[100][100]; // make larger than required

	// Initialize the maze
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			maze[i][j] = ' ';
		}

	int row = 0;
	int startRow, startCol;

	// Read the file line by line an initialize the maze
	string line;
	while (getline(mazeFile, line)) {
		cout << line << endl;
		for (int i = 0; i < (int) line.length(); i++) {
			maze[row][i] = line[i];
			if (maze[row][i] == 'S') {
				startRow = row;
				startCol = i;
				maze[row][i] = ' ';
			}
		}
		row++;
	}

	cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;

	// figure out the number of rows and columns
	int rowSz = row;
	int colSz = line.length();
	
	bool foundEnd = false;

	string finaldir = "";
	string currDir = "";
	SolveMaze(startRow, startCol, maze, rowSz, colSz, foundEnd, finaldir, currDir);
	
	cout << "Directions: " << finaldir << endl;

	// Print out the maze with the path shown
	for (int i = 0; i < rowSz; i++) {
		for (int j = 0; j < colSz; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	
    return 0;
}

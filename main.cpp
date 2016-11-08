// Uzir R. Thapa
// CS 2 
// HW 4
// 11/17/2014
#include <iostream>
#include <fstream>
#include <string>



using namespace std;

const int MAX = 12;

void openInputFile(/*IN*/ifstream& inText );
void readMaze( /*IN*/ifstream& inText, int& maxRows, int& maxCols, char grid[][MAX]);
void Print (int& maxRows, int& maxCols, char grid[][MAX]);
bool Escape(char grid[][MAX], int startRow, int startCol, int maxRows, int maxCols, char& letter);
void Solve(char grid[][MAX], int row, int col, bool& free, char& letter);


int main( void )
{
	int maxRows, maxCols;
	char letter = 'a';
	char grid[MAX][MAX];
	ifstream inText;
	openInputFile(/*IN*/ inText );
	readMaze( /*IN*/inText, maxRows, maxCols, grid );

	if (Escape(grid, 1, 1, maxRows, maxCols, letter) == false)			// condition for No solution found
	{
		cout << "No Solution Found!" << endl;
		Print (maxRows, maxCols, grid);
	}
	else
		Print (maxRows, maxCols, grid);

  return 0;
}

void openInputFile(/*IN*/ifstream& inText )
{	
	inText.open( "maze.in" );
    if ( !inText )
    {
        cout << "Can't open the input file.";  
        exit(1);        // halts program                
    }
}

void readMaze( /*IN*/ifstream& inText, int& maxRows, int& maxCols, char grid[][MAX])
{
	int rowIndex, columnIndex;

	inText >> maxRows >> maxCols;
	string row;
	
		for (rowIndex = 1; rowIndex <= maxRows; rowIndex++)						// read maze by row first
		{
			inText >> row;
			for (columnIndex = 1; columnIndex <= maxCols; columnIndex++)		// read maze by column 
				grid[rowIndex][columnIndex] = row[columnIndex-1];
			grid[rowIndex][0] = '*';
			grid[rowIndex][maxCols+1] = '*';
		}
		for (columnIndex = 0; columnIndex <= maxCols+1; columnIndex++)			// Create barrier for maze
		{
			grid[0][columnIndex] = '*';
			grid[maxRows+1][columnIndex] = '*';

		}

}

void Print (int& maxRows, int& maxCols, char grid[][MAX])
{
	int rowIndex, columnIndex;
	
	cout << "Maze" << endl;
	for (rowIndex = 1 ; rowIndex <= maxRows; rowIndex++)						// Print each row
	{
		for (columnIndex = 1; columnIndex <= maxCols; columnIndex++)			// Print each column
			cout << " " << grid[rowIndex][columnIndex];
		cout << endl;
	}
	

}

void Solve(char grid[][MAX], int row, int col, int maxRows, int maxCols, bool& free, char& letter)
{
	
	if (!free && (grid [row][col]) == '.')										// condition for recursion
		if ((row == maxRows) && (col == maxCols))								// condition to exit recursion
		{
			grid[row][col] = letter;
			free = true;
		}
		else 
		{
	
			grid[row][col] = letter;	// add last letter in the maze
			if (letter != 'z')			// go back from z->a 
				letter++;
			else 
				letter = 'a';
			Solve( grid, row+1, col, maxRows, maxCols, free, letter);			// Recursive function moving down 1
			if (!free)
				Solve( grid, row-1, col, maxRows, maxCols, free, letter);		// Recursive function moving up 1
			if (!free)
				Solve( grid, row, col+1, maxRows, maxCols, free, letter);		// Recursive function moving right 1
			if (!free)
				Solve (grid, row, col-1, maxRows, maxCols, free, letter);		// Recursive function moving left 1
			if (!free)
			{
				grid[row][col] = '.';			// if trapped, replace backtracked letters with "."
				if (letter == 'a')
					letter = 'z';
				else							// backtracking letters
				letter--;
			}
			
		}

}

bool Escape(char grid[][MAX], int startRow, int startCol, int maxRows, int maxCols, char& letter)		
{
	bool free = false;			// true/false for getting through the maze
	Solve( grid, startRow, startCol, maxRows, maxCols, free, letter);
	return free;
}

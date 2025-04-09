#include "maze_algorithm.h"

// Function to visualize movement
void gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Function to record previous moves in 'rec array'
void record(int x, int y)
{
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}

// Function to add delay so we can observe
void delay(clock_t n)
{
	clock_t start = clock();
	while (clock() - start < n);
}

void forward(int* x, int* y, int dir)
{
	gotoxy(*x + 1, *y + 1);
	_putch(' ');

	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;

	record(*x, *y);
	gotoxy(*x + 1, *y + 1);
	_putch(MOUSE);
}

//return 1 if we are still in maze
int still_in_maze(int x, int y)
{
	if (x > 0 && x < MAZE_SIZE - 1 && y > 0 && y < MAZE_SIZE - 1)
		return 1;
	else
		return 0;
}

// return 1 if there is a wall ahead
int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir)
{
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;
	return m[y][x];
}

void right(int* dir)
{
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}
void left(int* dir)
{
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}

void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir)
{
	gotoxy(x + 1, y + 1);
	_putch(MOUSE);
	record(x, y);

	forward(&x, &y, dir);
	while (still_in_maze(x, y))
	{
		delay(100);
		right(&dir);
		while (wall_ahead(m, x, y, dir))
		{
			left(&dir);
		}
		forward(&x, &y, dir);
	}
	record(-1, -1); // To record that we have escaped the maze
}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+--+-+-+-+-+-+
// fucntion to remove duplicate paths
// and find the shortest path
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+--+-+-+-+-+-+

int del_path(int i, int j)
{
	int k = i;

	while (rec[j] >= 0)
	{
		rec[i++] = rec[j++];
	}

	rec[i] = -1; // Mark the new end of the path

	return k; // Return the updated index to continue path processing
}

void shortest_path()
{
	int i = 0;
	while (rec[i] >= 0)
	{
		// From current index i, check for overlapping paths in the remaining route
		int j = i + 2;
		while (rec[j] >= 0)
		{
			// If a later coordinate matches the current one, it means there's a redundant path
			if (rec[i] == rec[j] && rec[i + 1] == rec[j + 1])
			{
				// Overwrite the redundant segment to shorten the path
				i = del_path(i, j);
				j = i + 2; 
			}
			else
			{
				j += 2;
			}
		}

		i = i + 2; 
	}

	// Display the final shortest path visually on the screen
	i = 0;
	while (rec[i] >= 0)
	{
		int x = rec[i++];
		int y = rec[i++];
		gotoxy(x + 1, y + 1);
		_putch(MOUSE);
		delay(100);
		gotoxy(x + 1, y + 1);
		_putch(' ');
	}
}
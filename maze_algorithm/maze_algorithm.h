#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAZE_SIZE 19
#define MOUSE '@' 

#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8

extern int* rec;
extern int sx, sy;
extern int maze[MAZE_SIZE][MAZE_SIZE];

void gotoxy(int x, int y);
void record(int x, int y);
void delay(int milliseconds);
void forward(int* x, int* y, int dir);
int still_in_maze(int x, int y);
int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir);
void right(int* dir);
void left(int* dir);
void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir);
int del_path(int i, int j);
void shortest_path();


#endif
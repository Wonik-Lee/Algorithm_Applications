#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int canvas[7][7] = {
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 0, 0,
	0, 1, 0, 0, 0, 1, 0,
	0 ,1, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 1, 0, 0,
	0, 0, 1, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0 
};

// ===================== [Recursive filling method] ==================================

void recur_fill(int x, int y)
{
	// return if the cell is a wall or is already filled
	if (canvas[y][x] == 1 || canvas[y][x] == 2) {
		return;
	}
	else {
		canvas[y][x] = 2;
		recur_fill(x - 1, y);
		recur_fill(x + 1, y);
		recur_fill(x, y - 1);
		recur_fill(x, y + 1);
	}
}

// ===================== [Non-Recursive filling method with Stack] =====================

int stack[MAX];
int top;

void init_stack() {
	top = -1;
}

int push(int t) {
	if (top >= MAX - 1) {
		printf("Stack overflow\n");
		return -1;
	}
	return stack[++top] = t;
}

int pop() {
	if (top < 0) {
		printf("Stack underflow\n");
		return -1;
	}
	return stack[top--];
}

int is_stack_empty() {
	return top < 0;
}

void non_recur_fill(int x, int y) {
	init_stack();
	push(x);
	push(y);

	while (!is_stack_empty()) {
		y = pop();
		x = pop();
		if (canvas[y][x] == 0) {  // !(terminate_condition)
			canvas[y][x] = 2;
			push(x);
			push(y - 1);
			push(x + 1);
			push(y);
			push(x);
			push(y + 1);
			push(x - 1);
			push(y);
		}
	}
}


void main()
{
	// fill inside
	non_recur_fill(3, 3);

	// print canvas
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%d", canvas[i][j]);
		}
		printf("\n");
	}

}

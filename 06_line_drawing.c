#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLK 20


void recursive_line(int* canvas, int x1, int y1, int x2, int y2)
{
	float dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (dist < sqrt(2)) {
		return;
	}

	int cx = (x1 + x2) / 2;
	int cy = (y1 + y2) / 2;

	// Since canvas is a 1D array, we calculate the index as (cy * BLK + cx) to simulate 2D access
	*(canvas + cy * BLK + cx) = 1;

	recursive_line(canvas, x1, y1, cx, cy);
	recursive_line(canvas, cx, cy, x2, y2);
}


void main()
{
	int i, j;
	int x1, y1, x2, y2;
	int* canvas = (int*)calloc(BLK * BLK, sizeof(int));

	printf("Input x1, y1: ");
	scanf("%d%d", &x1, &y1);
	printf("Input x2, y2: ");
	scanf("%d%d", &x2, &y2);


	recursive_line(canvas, x1, y1, x2, y2);

	*(canvas + y1 * BLK + x1) = 1;
	*(canvas + y2 * BLK + x2) = 1;


	for (i = 0; i < BLK; i++) {
		for (j = 0; j < BLK; j++) {
			printf("%-2d", canvas[i*BLK+j]);
		}
		printf("\n");
	}

}

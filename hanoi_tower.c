#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 10

// ===================== [Recursive Hanoi Functions] =====================

void move_recursive(int from, int to) {
    printf("R: move %d -> %d\n", from, to);
}

void hanoi(int n, int from, int by, int to) {
    if (n == 1) {
        move_recursive(from, to);
    }
    else {
        hanoi(n - 1, from, to, by);
        move_recursive(from, to);
        hanoi(n - 1, by, from, to);
    }
}

// ===================== [Non-Recursive Hanoi with Stack] =====================

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

void move(int from, int to) {
    printf("NR: move %d -> %d\n", from, to);
}

void nr_hanoi(int n, int from, int by, int to) {
    int done = 0;
    init_stack();
    while (!done)
    {
        while (n > 1)
        {
            push(to);
            push(by);
            push(from);
            push(n);
            n--;
            push(to);
            to = by;
            by = pop();
        }
        move(from, to);

        if (!is_stack_empty())
        {
            n = pop();
            from = pop();
            by = pop();
            to = pop();
            move(from, to);
            n--;
            push(from);
            from = by;
            by = pop();
        }
        else
        {
            done = 1;
        }
    }
}



int main()
{
	int j = 0;
	int n;
	printf("\nIf you want to quit, input -1:");
	while (1) {
		printf("\nInput the height of hanoi tower:");
		scanf("%d", &n);
		if (n == -1) {
			return 0;
		}
		hanoi(n, 1, 2, 3);
	}

	return 0;
}
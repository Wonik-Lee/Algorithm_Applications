#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void Eratos_func(int n); // Finds all prime numbers less than n

int main()
{
	int n;
	printf("Input number: ");
	scanf("%d", &n);
	Eratos_func(n);
	return 0;
}

void Eratos_func(int n)
{

	if (n < 3) {
		printf("No prime number.\n");
		return;
	}

	int* arr = (int*)calloc(n, sizeof(int));
	
	arr[0] = arr[1] = 1; //0 and 1 is not the prime number

	for (int i = 2; i * i < n; i++)  // or i <= sqrt(n)
	{
		if (arr[i]==0)
		{
			for (int j = i * i; j < n; j += i)
			{
				arr[j] = 1;
			}
		}
	}

	printf("Prime numbers less than %d: ", n);
	for (int i = 2; i < n; i++)
	{
		if (arr[i]==0)
		{
			printf("%d ", i);
		}
	}

	free(arr);

	return;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int a_la_russe(int a, int b)
{
	int c=0;
	while (a > 0)
	{
		if (a % 2 == 1) {
			c += b;
		}
		a = a / 2;
		b = b * 2;
	}
	return c;
}

int main()
{
	int a, b;

	printf("���� �� �� �Է� : ");
	scanf("%d%d", &a, &b);

	int result = a_la_russe(a, b);

	printf("\n��� : %d",result);


	return 0;
}
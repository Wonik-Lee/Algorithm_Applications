#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int gcd(int A, int B); //Computing gcd by Euclidean algorithm

void main()
{
	int A, B;
	int result;

	printf("Input 2 number :");
	scanf("%d%d", &A, &B);

	result = gcd(A, B);

	printf("gcd is %d", result);
}

int gcd(int A, int B) {
	
	int r = A % B;; //for remainder

	while (r != 0) {
		A = B;
		B = r;
		r = A % B;
	}

	return B;
}


//recursion version
int gcd_recursion(int A, int B) {
    if (B == 0) // Base case: if B is zero, the GCD is A
        return A;
    else 
        return gcd_recursion(B, A % B); // Recursive call with the remainder
}

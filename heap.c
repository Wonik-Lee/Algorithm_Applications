#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_NODE 100


// k�� ���� ���� ����
void upheap(int* a, int k) 
{
	int v;
	v = a[k]; // ��� ���� ���� ������ ����
	a[0] = INT_MAX;

	// �θ��庸�� �� ũ�� �÷���
	while (a[k / 2] <= v && k / 2 > 0) {
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}

void downheap(int* a, int N, int k)
{
	int i, v;
	v = a[k];
	while (k <= N / 2) {
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}


// v�� ���� insert�� ������
void insert(int* a, int* N, int v)
{
	a[++(*N)] = v; // v�� ���� ���� ����(hn)+1 �ε����� ����
	upheap(a, *N); // ���ο� �����Ͱ� ��������, ���Ľ���
}

int extract(int* a, int* N)
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);

	return v;
}


// N�� ���� ����
void heap_sort(int* a, int N)
{
	int i;
	int hn = 0; // ���� ���� ����ִ� ��� ��

	for (i = 1; i <= N; i++) {
		insert(a, &hn, a[i]); 
	}

	for (i = hn; i >= 1; i--) {
		a[i] = extract(a, &hn);  // ���� ��Ʈ������ �� ���� �������� heap�迭 �ڿ������� ����
	}
}


// heap sort�� �������� �����ϱ�
void main()
{
	int heap[MAX_NODE]; 
	int len = 0;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		heap[i + 1] = rand() % 10; // heap[1] ���� ����
		len++;                     // len�� �������� ����
		printf("%d ", heap[i + 1]);
	}
	printf("\n");

	heap_sort(heap, len);   

	for (int i = 1; i <= len; i++) {
		printf("%d ", heap[i]);
	}

}
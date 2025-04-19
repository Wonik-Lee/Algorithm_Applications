#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_NODE 100


// k는 현재 힙의 길이
void upheap(int* a, int k) 
{
	int v;
	v = a[k]; // 잠시 새로 들어온 데이터 저장
	a[0] = INT_MAX;

	// 부모노드보다 더 크면 올려줌
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


// v는 힙에 insert할 데이터
void insert(int* a, int* N, int v)
{
	a[++(*N)] = v; // v를 현재 힙의 길이(hn)+1 인덱스에 저장
	upheap(a, *N); // 새로운 데이터가 들어왔으니, 정렬시작
}

int extract(int* a, int* N)
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);

	return v;
}


// N은 힙의 길이
void heap_sort(int* a, int N)
{
	int i;
	int hn = 0; // 현재 힙에 들어있는 노드 수

	for (i = 1; i <= N; i++) {
		insert(a, &hn, a[i]); 
	}

	for (i = hn; i >= 1; i--) {
		a[i] = extract(a, &hn);  // 제일 루트노드부터 후 순위 노드까지를 heap배열 뒤에서부터 저장
	}
}


// heap sort로 오름차순 정렬하기
void main()
{
	int heap[MAX_NODE]; 
	int len = 0;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		heap[i + 1] = rand() % 10; // heap[1] 부터 저장
		len++;                     // len은 데이터의 길이
		printf("%d ", heap[i + 1]);
	}
	printf("\n");

	heap_sort(heap, len);   

	for (int i = 1; i <= len; i++) {
		printf("%d ", heap[i]);
	}

}

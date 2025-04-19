#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 50
#define MAX_EDGE 100
#define ONLY_FIND 0
#define UNION 1

int parent[MAX_NODE];
int height[MAX_NODE];
int cost = 0;
int nheap = 0;
int heap[MAX_NODE];
FILE* fp;

typedef struct edge {
	int v1, v2;
	int weight;
}edge;

edge Edge[MAX_EDGE];


int name2int(char c);
char int2name(int i);
void visit(int e);
void find_init(int elem);

void pq_init(void);
int pq_empty(void);
void upheap(int h[], int k);
void downheap(int h[], int k);
void pq_insert(int h[], int v);
int pq_extract(int h[]);

void input_edge(edge e[], int* V, int* E);

void union_set(int elem, int asso);
int find_set(int elem, int asso, int flag);

void kruskal(edge e[], int V, int E);


void main()
{
	int V, E;

	fp = fopen("graph.txt", "rt");

	input_edge(Edge, &V, &E);

	printf("\n\nVisited edge of minimum spanning tree\n");

	kruskal(Edge, V, E);

	printf("\n\nMinimum cost is %d\n", cost);

	fclose(fp);
}



//=====================================[Kruscal algorithm]=========================================

void kruskal(edge e[], int V, int E) {
	int n, val = 0;
	find_init(V);
	pq_init();

	//엣지 개수만큼 힙을 생성
	for (n = 0; n < E; n++) {
		pq_insert(heap, n);
	}

	n = 0; // 선택되는 edge의 개수 . 얼만큼 방문했는지 확인
	while (!pq_empty()) {
		val = pq_extract(heap); // 가중치 낮은 노드를 겟

		if (find_set(e[val].v1, e[val].v2, UNION)) { // 같은 집합이 아니라면 같은 집합으로 묶어준 뒤
			visit(val);   //그 엣지를 방문하고,
			n++;
		}
		if (n == V - 1) break;
	}
}


//=====================================[Union find]=========================================

void find_init(int elem) {
	for (int i = 0; i < elem; i++) {
		parent[i] = -1;
	}
}

// 같은집합인지 아닌지 여부를 확인. 같은 집합이 아니면 같은 집합으로 묶어주기
int find_set(int elem, int asso, int flag) {
	int i = elem, j = asso;

	while (parent[i] >= 0) {
		i = parent[i];
	}
	while (parent[j] >= 0) {
		j = parent[j];
	}
	if (flag == UNION && i != j) {
		union_set(i, j);           // i와 j가 다르다면 같은 집합으로 묶어주기
	}
	return (i != j); //서로 다르면 1을 반환, 같으면 0을 반환
}


void union_set(int elem, int asso) {
	parent[elem] = asso;
}


//=====================================[Priority queue]=========================================

void pq_init(void) {
	nheap = 0;
}

int pq_empty(void) {
	if (nheap == 0) return 1;
	return 0;
}

void pq_insert(int h[], int v) {
	h[++nheap] = v;
	upheap(h, nheap);
}

int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;
}


void upheap(int h[], int k) {
	int v = h[k];

	while (k / 2 > 0 && Edge[h[k / 2]].weight >= Edge[v].weight) {
		h[k] = h[k / 2];
		k /= 2;
	}
	h[k] = v;
}

void downheap(int h[], int k) {
	int i;
	int v = h[k];

	while (k <= nheap / 2) {
		i = k << 1;

		if (i < nheap && Edge[h[i]].weight > Edge[h[i + 1]].weight) i++;

		if (Edge[v].weight <= Edge[h[i]].weight) break;

		h[k] = h[i];
		k = i;
	}
	h[k] = v;
}


//=====================================[Utility]=========================================

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return 'A' + i;
}

void visit(int e) {
	printf("%c%c ", int2name(Edge[e].v1), int2name(Edge[e].v2));
	cost += Edge[e].weight;
}

// Edge 입력
void input_edge(edge e[], int* V, int* E) {
	char vertex[3];
	int i, j, w;
	printf("\nInput number of nodes and edges\n");

	fscanf(fp, "%d %d", V, E);
	printf("\nInput two nodes consisting of edge and its weight -> ");
	for (j = 0; j < *E; j++) {
		fscanf(fp, "%s %d", vertex, &w);

		vertex[2] = NULL;

		e[j].v1 = name2int(vertex[0]);
		e[j].v2 = name2int(vertex[1]);
		e[j].weight = w;
	}
}

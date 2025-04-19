#define _CRT_SECURE_NO_WARNINGS
#include "PFS.h"


node* G[MAX_NODE];  
int heap[MAX_NODE];     // heap array (인덱스 저장)
int check[MAX_NODE];    // 힙 배열 (가중치 저장) ----> parent[i]노드에서 i노드로 가는 간선의 가중치를 저장
int parent[MAX_NODE];   // 각 인덱스의 부모노드를 저장
FILE* fp;
int nheap = 0;          // heap의 길이


//=======================================[PFS]============================================

void PFS_adjlist(node* g[], int V)
{
    int i;
    node* t;
    pq_init();

    for (i = 0; i < V; i++) {
        check[i] = UNSEEN;    // 힙의 가중치를 UNSEEN 상태로 초기화
        parent[i] = 0;
    }

    for (i = 0; i < V; i++) {

        if (check[i] == UNSEEN) {        // UNSEEN 노드는 아직 본적도 없는 노드. 루트 노드만 들어가는 조건문
            parent[i] = -1;              // i는 루트노드의 인덱스. 루트노드의 부모는 없으므로 -1로 설정
            pq_update(heap, i, UNSEEN);  // 루트노드를 힙에 넣어서 힙 생성

            // 힙이 빌때까지(= 루트노드의 자식을 다 PFS 할 때 까지)
            while (!pq_empty()) {
                print_heap(heap);

                i = pq_extract(heap);    // 힙의 현재 루트노드를 i에 저장, 힙 재정렬

                check[i] = -check[i];    // 방문하면 가중치를 양수로 전환
                visit(i);

                // 방문한 노드의 인접 노드의 가중치 살펴보기
                for (t = g[i]; t != NULL; t = t->next) {
          
                    if (check[t->vertex] < 0)   // 그 중에 음수 가중치를 가진 애들은 미방문인 상태
                        
                        if (pq_update(heap, t->vertex, -t->weight))
                            parent[t->vertex] = i;                  // 업데이트가 되었으면 부모노드 업데이트
                }
            }
        }
    }
}


//===================================[Priority queue (heap)]========================================

void pq_init(void) {
    nheap = 0;
}

int pq_empty(void) {
    if (nheap == 0) return 1;
    return 0;
}


// v는 현재 노드의 인덱스. 예) A = 0, B = 1
// p는 현재 노드의 가중치. 예) B:2 면 p는 -2 (아직 인접노드 업데이트중이므로 미방문이니까 음수 표시)
int pq_update(int h[], int v, int p)
{
    // UNSEEN노드(미방문,스캔도 안한 노드)일때, 즉 새로 추가할 때
    if (check[v] == UNSEEN) {
        h[++nheap] = v;         // heap에 추가
        check[v] = p;           // check배열에 가중치(미방문) 저장.
        upheap(h, nheap);       // 힙 정렬
        return 1;
    }
    // 이미 스캔했던 노드일때, 더 우선순위가 높은 가중치인지 체크해줌
    else {                  
        if (check[v] < p) {             // 가중치가 음수상태이므로 더 큰게 우선순위가 높음(-5 < -1)
            check[v] = p;               
            adjust_heap(h, nheap);      // 가중치 업데이트했으므로 힙 다시 정렬
            return 1;
        }
        else return 0;                  // 이미 스캔도 했고, 가중치도 건드릴 게 없으면 업데이트 x
    }
}


// k는 nheap(heap[]의 길이)
void upheap(int h[], int k) 
{
    int v = h[k]; // v에 맨 끝 노드의 인덱스(알파벳)를 저장

    // 가중치가 음수상태이므로 더 큰 값이 우선순위가 높음.(ex : -5 < -1)
    // 루트노드가 아님 && 부모노드보다 자식노드가 더 크거나 같다면
    while (k / 2 > 0 && check[h[k / 2]] <= check[v]) {   
        h[k] = h[k / 2]; // 부모를 자식 자리로
        k /= 2;          // 현재 k는 한칸 위로 올라감
    }
    h[k] = v;
}


// 가중치 갱신.
void adjust_heap(int h[], int n) {
    int k;
    for (int k = n / 2; k >= 1; k--) {
        downheap(h, k);
    }
}


// 루트노드를 추출, 힙 재정렬
int pq_extract(int h[]) {
    int v = h[1];
    h[1] = h[nheap--]; // 재정렬을 위해 힙배열 맨 뒤의 노드를 루트로 가져옴
    downheap(h, 1);
    return v;          
}


// k노드부터 자식들을 검사
void downheap(int h[], int k)
{
    int i, v;
    v = h[k]; // v에 루트 노드를 저장 (adjust에서는 각 부모노드)

    // k <= nheap/2 인 k는 자식이 있는 노드들
    while (k <= nheap / 2) {
        i = k << 1;    // k가 나(부모), i는 왼쪽 자식 인덱스가 됨. h[k] 가 부모, h[i]가 왼쪽 자식 상태.

        if (i < nheap && check[h[i]] < check[h[i + 1]]) // i>nheap이면 크기 초과한거니까 진짜 자식이 아님.
            i++;                       // 왼쪽 자식보다 오른쪽 자식이 더 크면, i++해서 오른쪽 자식을 올릴것.

        if (check[v] >= check[h[i]]) // 나(부모)가 더 크면 더이상 정렬할 필요 없음.
            break;

        h[k] = h[i];        // 자식중 하나가 지금 나보다 더 크니까 자식을 지금 내 자리에 저장
        k = i;              // 인덱스도 한칸 내려감
    }
    h[k] = v;
}



//===================================[Utilities]=======================================

int name2int(char c) {
    return c - 'A';
}

char int2name(int i) {
    return 'A' + i;
}

void visit(int i) {
    printf(" -> %c ", int2name(i));
}

void print_heap(int h[]) {
    int i;
    printf("\n");
    for (i = 1; i <= nheap; i++) {
        printf("%c:%d ", int2name(h[i]), check[h[i]]);
    }
}

// tree 출력
void print_tree(int tree[], int n) {
    int i;
    printf("\n\nTree structure\n");
    printf("son     ");
    for (i = 0; i < n; i++)
        printf("%c  ", int2name(i));
    printf("\n------------------------------\n");
    printf("parent  ");
    for (i = 0; i < n; i++) {
        if (i == 0)
            printf("    ");
        else
            printf("%c  ", int2name(tree[i]));
    }
}

// 최소 비용 출력. c[]는 check배열
void print_cost(int check[], int V) {
    int total = 0;
    for (int i = 1; i < V; i++) {

        if (check[i] != UNSEEN) {
            total += check[i];
        }
    }

    printf("%d\n", total);
}


//=================================[Graph in/out]======================================

void input_adjlist(node* g[], int* V, int* E)
{
    char vertex[3];
    int i, j, w;
    node* t;

    printf("\nInput number of nodes & edges\n");
    fscanf(fp, "%d %d", V, E);
    for (i = 0; i < *V; i++) {
        g[i] = NULL;
    }

    printf("\nInput two nodes of edge and weight -> ");
    for (j = 0; j < *E; j++) {
        fscanf(fp, "%s %d", vertex, &w);

        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[1]);
        t->weight = w;
        t->next = g[name2int(vertex[0])];
        g[name2int(vertex[0])] = t;

        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[0]);
        t->weight = w;
        t->next = g[name2int(vertex[1])];
        g[name2int(vertex[1])] = t;
    }
}


void print_adjlist(node* g[], int V)
{
    int i;
    node* t;
    for (i = 0; i < V; i++) {
        printf("%c", int2name(i));
        for (t = g[i]; t != NULL; t = t->next) {
            printf("-> %c:%d ", int2name(t->vertex), t->weight);
        }
        printf("\n");
    }
}
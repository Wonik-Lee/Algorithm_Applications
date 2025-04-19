#define _CRT_SECURE_NO_WARNINGS
#include "PFS.h"


node* G[MAX_NODE];  
int heap[MAX_NODE];     // heap array (�ε��� ����)
int check[MAX_NODE];    // �� �迭 (����ġ ����) ----> parent[i]��忡�� i���� ���� ������ ����ġ�� ����
int parent[MAX_NODE];   // �� �ε����� �θ��带 ����
FILE* fp;
int nheap = 0;          // heap�� ����


//=======================================[PFS]============================================

void PFS_adjlist(node* g[], int V)
{
    int i;
    node* t;
    pq_init();

    for (i = 0; i < V; i++) {
        check[i] = UNSEEN;    // ���� ����ġ�� UNSEEN ���·� �ʱ�ȭ
        parent[i] = 0;
    }

    for (i = 0; i < V; i++) {

        if (check[i] == UNSEEN) {        // UNSEEN ���� ���� ������ ���� ���. ��Ʈ ��常 ���� ���ǹ�
            parent[i] = -1;              // i�� ��Ʈ����� �ε���. ��Ʈ����� �θ�� �����Ƿ� -1�� ����
            pq_update(heap, i, UNSEEN);  // ��Ʈ��带 ���� �־ �� ����

            // ���� ��������(= ��Ʈ����� �ڽ��� �� PFS �� �� ����)
            while (!pq_empty()) {
                print_heap(heap);

                i = pq_extract(heap);    // ���� ���� ��Ʈ��带 i�� ����, �� ������

                check[i] = -check[i];    // �湮�ϸ� ����ġ�� ����� ��ȯ
                visit(i);

                // �湮�� ����� ���� ����� ����ġ ���캸��
                for (t = g[i]; t != NULL; t = t->next) {
          
                    if (check[t->vertex] < 0)   // �� �߿� ���� ����ġ�� ���� �ֵ��� �̹湮�� ����
                        
                        if (pq_update(heap, t->vertex, -t->weight))
                            parent[t->vertex] = i;                  // ������Ʈ�� �Ǿ����� �θ��� ������Ʈ
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


// v�� ���� ����� �ε���. ��) A = 0, B = 1
// p�� ���� ����� ����ġ. ��) B:2 �� p�� -2 (���� ������� ������Ʈ���̹Ƿ� �̹湮�̴ϱ� ���� ǥ��)
int pq_update(int h[], int v, int p)
{
    // UNSEEN���(�̹湮,��ĵ�� ���� ���)�϶�, �� ���� �߰��� ��
    if (check[v] == UNSEEN) {
        h[++nheap] = v;         // heap�� �߰�
        check[v] = p;           // check�迭�� ����ġ(�̹湮) ����.
        upheap(h, nheap);       // �� ����
        return 1;
    }
    // �̹� ��ĵ�ߴ� ����϶�, �� �켱������ ���� ����ġ���� üũ����
    else {                  
        if (check[v] < p) {             // ����ġ�� ���������̹Ƿ� �� ū�� �켱������ ����(-5 < -1)
            check[v] = p;               
            adjust_heap(h, nheap);      // ����ġ ������Ʈ�����Ƿ� �� �ٽ� ����
            return 1;
        }
        else return 0;                  // �̹� ��ĵ�� �߰�, ����ġ�� �ǵ帱 �� ������ ������Ʈ x
    }
}


// k�� nheap(heap[]�� ����)
void upheap(int h[], int k) 
{
    int v = h[k]; // v�� �� �� ����� �ε���(���ĺ�)�� ����

    // ����ġ�� ���������̹Ƿ� �� ū ���� �켱������ ����.(ex : -5 < -1)
    // ��Ʈ��尡 �ƴ� && �θ��庸�� �ڽĳ�尡 �� ũ�ų� ���ٸ�
    while (k / 2 > 0 && check[h[k / 2]] <= check[v]) {   
        h[k] = h[k / 2]; // �θ� �ڽ� �ڸ���
        k /= 2;          // ���� k�� ��ĭ ���� �ö�
    }
    h[k] = v;
}


// ����ġ ����.
void adjust_heap(int h[], int n) {
    int k;
    for (int k = n / 2; k >= 1; k--) {
        downheap(h, k);
    }
}


// ��Ʈ��带 ����, �� ������
int pq_extract(int h[]) {
    int v = h[1];
    h[1] = h[nheap--]; // �������� ���� ���迭 �� ���� ��带 ��Ʈ�� ������
    downheap(h, 1);
    return v;          
}


// k������ �ڽĵ��� �˻�
void downheap(int h[], int k)
{
    int i, v;
    v = h[k]; // v�� ��Ʈ ��带 ���� (adjust������ �� �θ���)

    // k <= nheap/2 �� k�� �ڽ��� �ִ� ����
    while (k <= nheap / 2) {
        i = k << 1;    // k�� ��(�θ�), i�� ���� �ڽ� �ε����� ��. h[k] �� �θ�, h[i]�� ���� �ڽ� ����.

        if (i < nheap && check[h[i]] < check[h[i + 1]]) // i>nheap�̸� ũ�� �ʰ��ѰŴϱ� ��¥ �ڽ��� �ƴ�.
            i++;                       // ���� �ڽĺ��� ������ �ڽ��� �� ũ��, i++�ؼ� ������ �ڽ��� �ø���.

        if (check[v] >= check[h[i]]) // ��(�θ�)�� �� ũ�� ���̻� ������ �ʿ� ����.
            break;

        h[k] = h[i];        // �ڽ��� �ϳ��� ���� ������ �� ũ�ϱ� �ڽ��� ���� �� �ڸ��� ����
        k = i;              // �ε����� ��ĭ ������
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

// tree ���
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

// �ּ� ��� ���. c[]�� check�迭
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
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100


//Simple linked list structure
typedef struct node {
    int vertex;
    struct node* next;
} node;


node* GL[MAX_NODE];
int son_of_root = 0;
int check[MAX_NODE] = { 0 };
int order = 0;

//����->���� or ����->���� ġȯ�Լ�
int name2int(char c) {
    return c - 'A';
}
char int2name(int i) {
    return i + 'A';
}



void input_adjlist(node* a[], int* V, int* E) {
    char vertex[3];
    int i, j;
    node* t;
    printf("\nInput number of node & edge\n");
    scanf("%d %d", V, E);
    for (i = 0; i < *V; i++) a[i] = NULL;

    for (j = 0; j < *E; j++) {
        printf("\nInput two node consisting edge\n");
        scanf("%s", vertex);

        i = name2int(vertex[0]);
        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[1]);
        t->next = a[i];
        a[i] = t;

        i = name2int(vertex[1]);
        t = (node*)malloc(sizeof(node));
        t->vertex = name2int(vertex[0]);
        t->next = a[i];
        a[i] = t;
    }
}


int AP_recur(node* a[], int i)
{
    node* t;
    int min; // ���� ����(i)�� ��Ʈ�� �ϴ� ����Ʈ�� ��ü�� �ö� �� �ִ� ���� ���� ������
    int m;
    check[i] = min = ++order;  // �湮 ������ �����ϴ� �迭
    for (t = a[i]; t != NULL; t = t->next) {
        if (i == 0 && check[t->vertex] == 0)
            son_of_root++;   //��Ʈ���� �������� �б� ���� ���� ����
        if (check[t->vertex] == 0) {
            m = AP_recur(a, t->vertex);
            if (m < min) min = m;
            if (m >= check[i] && i != 0)
                printf("* %c %2d : %d\n", int2name(i), check[i], m);   // ������ ǥ��
            else
                printf("  %c %2d : %d\n", int2name(i), check[i], m);   // ������ �ƴ�
        }
        else
            if (check[t->vertex] < min)
                min = check[t->vertex];
    }
    return min;
}


// finding Articulation point
void AP_search(node* a[], int V)
{
    int i, n = 0;
    node* t;
    for (i = 0; i < V; i++) check[i] = 0;
    order = son_of_root = 0;

    AP_recur(a, 0);
    if (son_of_root > 1) printf("* ");  // A�� ��Ʈ�ε� ��Ʈ�� �ڽ��� 2 �̻��̸� �������̴�.
    else printf("  ");
    printf("%c son : %d\n", int2name(0), son_of_root);
}



int main()
{
    int V, E;
    input_adjlist(GL, &V, &E);
    AP_search(GL, V);


    return 0;
}
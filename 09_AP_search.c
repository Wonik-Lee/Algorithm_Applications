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

//영어->숫자 or 숫자->영어 치환함수
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
    int min; // 현재 정점(i)를 루트로 하는 서브트리 전체가 올라갈 수 있는 가장 작은 조상노드
    int m;
    check[i] = min = ++order;  // 방문 순번을 저장하는 배열

    for (t = a[i]; t != NULL; t = t->next) { 
        if (i == 0 && check[t->vertex] == 0)
            son_of_root++;   //루트에서 내려가는 분기 수를 세는 역할(son_of_root가 2 이상이면 루트도 단절점)
        if (check[t->vertex] == 0) {
            m = AP_recur(a, t->vertex);  // 자식들이 올라갈 수 있는 제일 상위 노드를 가져옴.
            if (m < min) min = m;        // m < min 이면 m이 더 상위노드니까, min을 m으로 업데이트.
            if (m >= check[i] && i != 0) // 현재 루트노드가 아니고, 자식들이 올라갈 수 있는 제일 상위 노드 m이 나(check[i])보다 낮다면, 단절점
                printf("* %c %2d : %d\n", int2name(i), check[i], m);   // 단절점 표시
            else
                printf("  %c %2d : %d\n", int2name(i), check[i], m);   // 단절점 아님
        }
        else // 이미 방문했던 노드라면 
            if (check[t->vertex] < min) // 그 노드가 min보다 더 상위 노드면 업데이트
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
    if (son_of_root > 1) printf("* ");  // A가 루트인데 루트도 자식이 2 이상이면 단절점이다.
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

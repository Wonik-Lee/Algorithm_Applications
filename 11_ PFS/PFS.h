#ifndef PFS_H
#define PFS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODE 100
#define UNSEEN (-INT_MAX)

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} node;


extern node* G[MAX_NODE];      // 그래프 저장 배열
extern int check[MAX_NODE];    // 가중치 저장 배열
extern int parent[MAX_NODE];   // 부모노드 저장
extern FILE* fp;               
extern int nheap;              // 힙에 저장된 원소 수
extern int heap[MAX_NODE];     // 힙 배열


// PFS function
void PFS_adjlist(node* g[], int V);


// Graph function
void input_adjlist(node* g[], int* V, int* E);
void print_adjlist(node* g[], int V);


// Priority queue
void pq_init();
int pq_empty();
int pq_update(int h[], int v, int p);
void upheap(int h[], int k);
void adjust_heap(int h[], int n);
int pq_extract(int h[]);
void downheap(int h[], int k);


// Utility function
int name2int(char c);
char int2name(int i);
void visit(int i);
void print_heap(int h[]);
void print_tree(int tree[], int n);
void print_cost(int c[], int V);

#endif /* PFS_H */

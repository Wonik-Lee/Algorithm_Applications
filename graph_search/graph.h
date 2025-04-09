#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define MAX_NODE 100


//Simple linked list structure
typedef struct node {
    int vertex;
    struct node* next;
} node;


//Double linked list structure
typedef struct _dnode
{
    int key;
    struct _dnode* prev;
    struct _dnode* next;
}dnode;


//Extern Global variables
extern int GM[MAX_NODE][MAX_NODE];
extern node* GL[MAX_NODE];
extern int stack[MAX];
extern int check[MAX_NODE];
extern int top;
extern dnode* head, * tail;


//type change functions
int name2int(char c);
char int2name(int i);


//  I/O functions
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E);
void print_adjmatrix(int a[][MAX_NODE], int V);
void input_adjlist(node* a[], int* V, int* E);
void print_adjlist(node* a[], int V);
void visit(int i);


//stack
int pop();
int push(int t);
int stack_empty();
void init_stack();


//queue
int put(int k);
int get();
int queue_empty();
void init_queue();


//DFS
void DFS_recur_matrix(int a[][MAX_NODE], int V, int i);
void DFS_adjmatrix(int a[][MAX_NODE], int V);
void nrDFS_adjmatrix(int a[][MAX_NODE], int V);
void DFS_recur_list(node* a[], int V, int i);
void DFS_adjlist(node* a[], int V);
void nrDFS_adjlist(node* a[], int V);


//BFS
void BFS_adjmatrix(int a[][MAX_NODE], int V);
void BFS_adjlist(node* a[], int V);


//count components
void count_components(int a[][MAX_NODE], int V);


#endif
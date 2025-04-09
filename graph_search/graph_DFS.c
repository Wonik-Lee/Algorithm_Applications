#include "graph.h"


int check[MAX_NODE];


//===================================[adj matrix]================================

// Recursive DFS using an adjacency matrix.
void DFS_recur_matrix(int a[][MAX_NODE], int V, int i) {
    int j;
    check[i] = 1;
    visit(i);
    for (j = 0; j < V; j++)
        if (a[i][j] == 1)
            if (check[j] == 0) {
                DFS_recur_matrix(a, V, j);
            }
}


// Calls DFS_recur_matrix for each unvisited vertex.
void DFS_adjmatrix(int a[][MAX_NODE], int V) {
    int i;
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++)
        if (check[i] == 0)
            DFS_recur_matrix(a, V, i);
}


// Non-recursive DFS using a stack (for adjacency matrix)
void nrDFS_adjmatrix(int a[][MAX_NODE], int V) {
    int i, j;
    init_stack();
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++) {
        if (check[i] == 0) {
            push(i);
            check[i] = 1;
            while (!stack_empty()) {
                i = pop();
                visit(i);
                for (j = 0; j < V; j++)
                    if (a[i][j] != 0 && check[j] == 0) {
                        push(j);
                        check[j] = 1;
                    }
            }
        }
    }
}

//===================================[adj list]================================

// Recursive DFS using adjacency list.
void DFS_recur_list(node* a[], int V, int i) {
    node* t;
    check[i] = 1;
    visit(i);
    for (t = a[i]; t != NULL; t = t->next)
        if (check[t->vertex] == 0)
            DFS_recur_list(a, V, t->vertex);
}


// Calls DFS_recur_list for each unvisited vertex.
void DFS_adjlist(node* a[], int V) {
    int i;
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++)
        if (check[i] == 0)
            DFS_recur_list(a, V, i);
}


// Non-recursive DFS using a stack (for adjacency list)
void nrDFS_adjlist(node* a[], int V) {
    int i, j, curr;
    node* t;
    init_stack();
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++) {
        if (check[i] == 0) {
            push(i);
            check[i] = 1;
            while (!stack_empty()) {
                curr = pop();
                visit(curr);
                for (t = a[curr]; t != NULL; t = t->next) {
                    if (check[t->vertex] == 0) {
                        push(t->vertex);
                        check[t->vertex] = 1;
                    }
                }
            }
        }
    }
}
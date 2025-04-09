#include "graph.h"



void BFS_adjmatrix(int a[][MAX_NODE], int V)
{
    int i, j;
    init_queue();
    for (i = 0; i < V; i++) check[i] = 0;

    for (i = 0; i < V; i++) {
        if (check[i] == 0) {
            put(i);
            check[i] = 1;
            while (!queue_empty()) {
                i = get();
                visit(i);
                for (j = 0; j < V; j++)
                    if (a[i][j] != 0)
                        if (check[j] == 0) {
                            put(j);
                            check[j] = 1;
                        }
            }
        }
    }
}


void BFS_adjlist(node* a[], int V)
{
    int i, curr;
    node* t;
    init_queue();
    for (i = 0; i < V; i++) check[i] = 0;
    for (i = 0; i < V; i++) {
        if (check[i] == 0) {
            put(i);
            check[i] = 1;
            while (!queue_empty()) {
                curr = get();
                visit(curr);
                for (t = a[curr]; t != NULL; t = t->next)
                    if (check[t->vertex] == 0) {
                        put(t->vertex);
                        check[t->vertex] = 1;
                    }
            }
        }
    }
}